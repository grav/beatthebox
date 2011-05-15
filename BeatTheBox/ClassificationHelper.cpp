//
//  ClassificationHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <assert.h>
#include "DSP.h"
#include <math.h>
#include "fftw3.h"
#include "ClassificationHelper.h"
#include "MFCC.h"
#include "SoundHelper.h"

using namespace std;

map<vector<double>,InstrumentClass> *ClassificationHelper::getFeatureMap(string flatFile){
    map<vector<double>,InstrumentClass> *result = new map<vector<double>,InstrumentClass>;
    
    map<string,InstrumentClass> *m = getMap(flatFile);
    map<string,InstrumentClass>::iterator it;
    // load file
    // calculate features
    // insert into map
    for(it = m->begin() ; it != m->end(); it++){
        double *samples; sf_count_t numSamples;
        double *means; double *vars;
        vector<double> key;
        string filename="/Users/grav/repositories/uni/feature/"+(*it).first;
        SoundHelper::loadMono(filename,samples,numSamples);
        getFeatures(samples, (int)numSamples, means, vars);
        key.assign(means, means+NUM_MELS);
        key.insert(key.end(), vars,vars+NUM_MELS);
        assert(key.size()==NUM_MELS*2);
        (*result)[key]=(*it).second;
    }
    
    return result;
}

map<string,InstrumentClass>* ClassificationHelper::getMap(string flatFile){
    
    map<string,InstrumentClass> *pClasses = new map<string, InstrumentClass>;
    
    FILE *pFile;
    long lSize;
    char *buffer;
    size_t result;
    
    pFile=fopen(flatFile.c_str(), "rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
    
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
    
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
    
    /* the whole file is now loaded in the memory buffer. */
    
    long i=0; // buffer pointer
    int j=0; // fileName pointer
    char fileName[1024];
    while(i<lSize){
        fileName[j]=buffer[i];
        j++;
        if(buffer[i]==0){ // null termination
            // get instrument class
            i++;
            InstrumentClass k = InstrumentClass((int)buffer[i]);
            string s = fileName;
            (*pClasses)[s]=k;
            j=0; // reset fileName pointer
        }
        i++;
    }
    
    // terminate
    fclose (pFile);
    free (buffer);
    return pClasses;
}



void ClassificationHelper::getSpectrogram(double *audio, int audioLength, int winSize, 
                                          double *&spectrogram, int &frames, int &bins){

    double *padded;
    int paddedLength;
    
    DSP::zeroPad(audio, audioLength, winSize, padded, paddedLength);
    
    frames = paddedLength/winSize;
    bins = winSize/2+1;
    
    assert(winSize*frames==paddedLength);

    spectrogram = new double[frames*bins];
    
    for(int i = 0; i<paddedLength; i+=winSize){
        double *in = DSP::hamming(DSP::copyRange(audio, i, winSize), winSize);
        fftw_complex *out;
        fftw_plan p;
        

        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*winSize);
        p = fftw_plan_dft_r2c_1d(winSize, in, out, FFTW_ESTIMATE);
        
        fftw_execute(p);
        
        // copy from out to spectrogram
        int frame = i/winSize;
        for(int bin=0;bin<bins;bin++){
            // TODO - normalize?
            spectrogram[frame*bins+bin]=DSP::length(out[bin]);
        }
        
        delete in;
        fftw_free(out);
        fftw_destroy_plan(p);
        
    }
    
}

void ClassificationHelper::getFeatures(double *audio, int audioLength, double *&means, double *&vars){
    int winSize = 256; // TODO make constant somewhere
    double *spectrogram;
    int frames; int bins;
    getSpectrogram(audio, audioLength, winSize, spectrogram, frames, bins);

    getStats(spectrogram, frames, bins, NUM_MELS, ^(double *a, int l) {
        return MFCC::getMFCCs(a,l);
    }, means, vars);
}

double ClassificationHelper::spectralCentroid(double *audio, int audioLength){
    double *sArr =  DSP::mapWithIndex(audio, audioLength, ^double(double x, int i) {
        return (i+1)*x;
    });
    double s = DSP::sum(sArr, audioLength);
    
    double sum = DSP::sum(audio, audioLength);
    double r= s/sum;
    
    // TODO the java version tests for NaN?
    return r==-INFINITY?0:r;
}

void ClassificationHelper::getStats(double *spectrums, int numSpectrums, int freqBins, int resultBins, 
                                    double* (^f)(double *audio, int audioLength), 
                                    double *&means, double *&variances){
    
    double results[numSpectrums*resultBins];
    for(int spec=0;spec<numSpectrums;spec++){
        double *result = f(&spectrums[spec*freqBins],freqBins);
        for(int bin=0;bin<resultBins;bin++){
            results[spec*resultBins+bin] = result[bin];
        }
    }
    
    means = new double[resultBins];
    variances = new double[resultBins];
    for(int bin = 0; bin<resultBins;bin++){
        double sum=0;
        for(int spec = 0; spec< numSpectrums;spec++){
            sum+=results[spec*resultBins+bin];
        }
        means[bin]=sum/numSpectrums;
        double varSum = 0;
        for(int spec = 0; spec< numSpectrums;spec++){
            varSum += pow(results[spec*resultBins+bin]-means[bin],2);
        }
        variances[bin] = varSum/(numSpectrums-1); // unbiased estimate
    }
}
    
