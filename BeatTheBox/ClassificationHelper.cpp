//
//  ClassificationHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ClassificationHelper.h"
#include "DSP.h"
#include <math.h>
#include "fftw3.h"
#include <assert.h>


void ClassificationHelper::getSpectrogram(double *audio, int audioLength, int winSize, 
                                          double *&spectrogram, int &frames){

    double *padded;
    int paddedLength;
    
    DSP::zeroPad(audio, audioLength, winSize, padded, paddedLength);
    
    frames = paddedLength/winSize;
    int bins = winSize/2+1;
    
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
        for(int bin=0;bin<bins;bin++){
            int frame = i/bins;
            // TODO - normalize?
            spectrogram[frame*bins+bin]=DSP::length(out[bin]);
        }
        
        fftw_destroy_plan(p);
//        fftw_free(in); 
        fftw_free(out);
        
    }
    
}

void ClassificationHelper::getFeatures(double *audio, int audioLength, double *&means, double *&vars){
    
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
        means[bin]=sum/resultBins;
        double varSum = 0;
        for(int spec = 0; spec< numSpectrums;spec++){
            varSum += pow(results[spec*resultBins+bin]-means[bin],2);
        }
        variances[bin] = varSum/(resultBins-1); // unbiased estimate
    }
}
    
