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
    
    
