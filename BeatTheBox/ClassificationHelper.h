//
//  ClassificationHelper.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

class ClassificationHelper{
public:
    static void getFeatures(double *audio, int audioLength, double *&means, double *&vars);
    
    static double spectralCentroid(double *audio, int audioLength);
    
//    static void getStats(double *spectrums, int numSpectrums, int freqBins
};

