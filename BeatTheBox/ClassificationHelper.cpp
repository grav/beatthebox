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

template <class T>
void ClassificationHelper<T>::getFeatureMap(string flatFile, map<vector<T>,InstrumentClass> *result){
    
    map<string,InstrumentClass> m;
    getMap(flatFile,&m);
    map<string,InstrumentClass>::iterator it;
    // load file
    // calculate features
    // insert into map
    int num = 0;
    for(it = m.begin() ; it != m.end(); it++){
        num++;
        cout << "Calculating features for sample " << num << " of " << m.size() << endl;
        vector<T> samples;
        string filename=PATH_PREFIX+(*it).first;
        SoundHelper::loadMono(filename,&samples);
        vector<T> key;
        getFeatures(&samples,&key);
        assert(key.size()==NUM_MELS*2);
        (*result)[key]=(*it).second;
    }
    
}

template <class T>
void ClassificationHelper<T>::getMap(string flatFile,map<string,InstrumentClass> *pClasses){
    
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
}



template <class T>
void ClassificationHelper<T>::getSpectrogram(vector<T> *audio, int winSize, 
                                          T *&spectrogram, int &frames, int &bins){

    vector<T> padded;
    DSP::zeroPad(audio, winSize, &padded);
    
    frames = (int)(padded.size())/winSize;
    bins = winSize/2+1;
    
    assert(winSize*frames==padded.size());

    spectrogram = new T[frames*bins];
    
    for(int i = 0; i<padded.size(); i+=winSize){
        vector<T> v(padded.begin()+i,padded.begin()+i+winSize);
        vector<T> in;
        DSP::hamming(&v,&in);
        fftw_complex *out;
        fftw_plan p;
        

        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*winSize);
        p = fftw_plan_dft_r2c_1d(winSize, &(in.front()), out, FFTW_ESTIMATE);
        
        fftw_execute(p);
        
        // copy from out to spectrogram
        int frame = i/winSize;
        for(int bin=0;bin<bins;bin++){
            spectrogram[frame*bins+bin]=length(out[bin]);
        }
        
        fftw_free(out);
        fftw_destroy_plan(p);
        
    }
    
}

template <class T>
void ClassificationHelper<T>::getFeatures(vector<T> *audio, vector<T> *r){
    int winSize = 256; // TODO make constant somewhere
    T *spectrogram, *means, *vars;
    int frames; int bins;
    getSpectrogram(audio, winSize, spectrogram, frames, bins);

    getStats(spectrogram, frames, bins, NUM_MELS, ^(T *a, int l) {
        return MFCC<T>::getMFCCs(a,l);
    }, means, vars);
    r->assign(means, means+NUM_MELS);
    r->insert(r->end(), vars,vars+NUM_MELS);
    delete[] spectrogram; delete[] means; delete[] vars;
}

template <class T>
T ClassificationHelper<T>::spectralCentroid(vector<T> *audio){
    vector<T> sArr;
    DSP::mapWithIndex(audio, ^T(T x, int i) {
        return (i+1)*x;
    },&sArr);
    T s = DSP::sum(&sArr);
    
    T sum = DSP::sum(audio);
    T r= s/sum;
    
    // TODO the java version tests for NaN?
    return r==-INFINITY?0:r;
}

template <class T>
void ClassificationHelper<T>::getStats(T *spectrums, int numSpectrums, int freqBins, int resultBins, 
                                    T* (^f)(T *audio, int audioLength), 
                                    T *&means, T *&variances){
    
    T results[numSpectrums*resultBins];
    for(int spec=0;spec<numSpectrums;spec++){
        T *result = f(&spectrums[spec*freqBins],freqBins);
        for(int bin=0;bin<resultBins;bin++){
            results[spec*resultBins+bin] = result[bin];
        }
        delete[] result;
    }
    
    means = new T[resultBins];
    variances = new T[resultBins];
    for(int bin = 0; bin<resultBins;bin++){
        T sum=0;
        for(int spec = 0; spec< numSpectrums;spec++){
            sum+=results[spec*resultBins+bin];
        }
        means[bin]=sum/numSpectrums;
        T varSum = 0;
        for(int spec = 0; spec< numSpectrums;spec++){
            varSum += pow(results[spec*resultBins+bin]-means[bin],2);
        }
        variances[bin] = varSum/(numSpectrums-1); // unbiased estimate
    }
}
    
template class ClassificationHelper<double>;