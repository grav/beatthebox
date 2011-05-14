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
    assert(numSamples>0);
    samples = new double[numSamples];
    sf_count_t read = handle.read(samples,numSamples);
    assert(read==numSamples);
}