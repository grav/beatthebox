//
//  ClassificationHelper.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "constants.h"
#include <map>
#include <vector>
#include "fftw3.h"
#include <math.h>

class ClassificationHelper{
public:
    static double length(fftw_complex c){
        return sqrt(pow(c[0],2)+pow(c[1],2));
    }

    static void getMap(std::string flatFile,std::map<std::string,InstrumentClass> *pClasses);
    
    static void getSpectrogram(std::vector<double> *audio, int winSize, 
                               double *&spectrogram, int &frames, int &bins);
    
    static std::vector<double> *getFeatures(std::vector<double> *audio);
    
    static double spectralCentroid(std::vector<double> *audio);
    
    static void getStats(double *spectrums, int numSpectrums, 
                         int freqBins, int resultBins,
                         double* (^f)(double *audio, int audioLength),
                         double *&means, double *&variances);

    static void getFeatureMap(std::string flatFile, std::map<std::vector<double>,InstrumentClass> *result);
    
};

