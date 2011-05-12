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
    
    means = new double[resultBins];
    variances = new double[resultBins];
    
    //TODO
    // apply f on each of the numSpectrums spectrums
    // update means and variances such that the result of means[i] is
    // the mean of the i'th result bin of f applied to the spectrum
}
    
    
