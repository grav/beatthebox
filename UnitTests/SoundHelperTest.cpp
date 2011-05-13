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

TEST(SoundHelperTest,LoadMono){
    std::string fileName = "/Users/grav/repositories/uni/feature/session2/mikkel_02.wav";
    
//    SndfileHandle handle(fileName); // alloc on stack
//    sf_count_t numSamples = handle.frames()*handle.channels();
    sf_count_t numSamples;
    double *samples;
    SoundHelper::loadMono(fileName,samples,numSamples);
    EXPECT_EQ(122880,numSamples);

}