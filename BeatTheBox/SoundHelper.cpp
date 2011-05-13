//
//  SoundHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SoundHelper.h"
#include <assert.h>
void SoundHelper::loadMono(std::string fileName, double *&samples, sf_count_t &numSamples){
    SndfileHandle handle(fileName); // alloc on stack
    numSamples = handle.frames()*handle.channels();
//    EXPECT_EQ(122880,numSamples);
    
    sf_count_t read = handle.read(samples,numSamples);
    assert(read==numSamples);
}