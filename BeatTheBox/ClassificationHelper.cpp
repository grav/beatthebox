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
    
    return isnan(r)?0:r;
}