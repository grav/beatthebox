//
//  ClassificationHelper.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

class ClassificationHelper{
public:
    static void getSpectrogram(double *audio, int audioLength, int winSize, 
                               double *&spectrogram, int &frames);
    
    static void getFeatures(double *audio, int audioLength, double *&means, double *&vars);
    
    static double spectralCentroid(double *audio, int audioLength);
    
    static void getStats(double *spectrums, int numSpectrums, 
                         int freqBins, int resultBins,
                         double* (^f)(double *audio, int audioLength),
                         double *&means, double *&variances);

};
