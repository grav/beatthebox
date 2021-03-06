//
//  SoundHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "SoundHelper.h"
#include <iostream>
#include "DSP.h"
#include "constants.h"
TEST(SoundHelperTest,LoadMono){
    std::string fileName = PATH_PREFIX+(std::string)"session2/mikkel_02.wav";
    
    vector<double> samples;
    SoundHelper::loadMono(fileName,&samples);
    EXPECT_EQ(122880,samples.size());

    
}

TEST(SoundHelperTest,SaveMono){
    std::string fileName = "/Users/grav/Desktop/test.wav";
    size_t length = 44100;
    vector<double> noise;
    DSP::noise(length,&noise);
    vector<double> noiseNorm;
    DSP::map(&noise, ^(double x){return x*.1-1;},&noiseNorm);
    SoundHelper::saveMono(fileName, &noiseNorm);
}