//
//  SoundHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "SoundHelper.h"
#include <iostream.h>
#include "DSP.h"
TEST(SoundHelperTest,LoadMono){
    std::string fileName = "/Users/grav/repositories/uni/feature/session2/mikkel_02.wav";
    
    sf_count_t numSamples;
    double *samples;
    SoundHelper::loadMono(fileName,samples,numSamples);
    EXPECT_EQ(122880,numSamples);

    
}

TEST(SoundHelperTest,SaveMono){
    std::string fileName = "/Users/grav/Desktop/test.wav";
    int length = 44100;
    double *noise = DSP::noise(length);
    double *noiseNorm = DSP::map(noise, length, ^(double x){return x*.1-1;});
    SoundHelper::saveMono(fileName, noiseNorm, length);
}