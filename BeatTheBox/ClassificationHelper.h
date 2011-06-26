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

// todo - maybe make namespace instead?

template <class T>
class ClassificationHelper{
public:
    static T length(fftw_complex c){
        return sqrt(pow(c[0],2)+pow(c[1],2));
    }

    static void getMap(std::string flatFile,std::map<std::string,InstrumentClass> *pClasses);
    
    static void getSpectrogram(std::vector<T> *audio, int winSize, 
                               T *&spectrogram, int &frames, int &bins);
    
    static void getFeatures(std::vector<T> *audio, std::vector<T> *r);
    
    static T spectralCentroid(std::vector<T> *audio);
    
    static void getStats(T *spectrums, int numSpectrums, 
                         int freqBins, int resultBins,
                         T* (^f)(T *audio, int audioLength),
                         T *&means, T *&variances);

    static void getFeatureMap(std::string flatFile, std::map<std::vector<T>,InstrumentClass> *result);
    
};

