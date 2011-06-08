//
//  SoundHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SoundHelper.h"
#include <assert.h>

void makeMono(double *samples, sf_count_t &numSamples);

void SoundHelper::loadMono(std::string fileName, double *&samples, sf_count_t &numSamples){
    SndfileHandle handle(fileName); // alloc on stack
    numSamples = handle.frames()*handle.channels();
    assert(numSamples>0);
    samples = new double[numSamples];
    sf_count_t read = handle.read(samples,numSamples);
    assert(read==numSamples);
}

void SoundHelper::saveMono(std::string fileName, double *samples, int numSamples){
    const int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    SndfileHandle handle(fileName,SFM_WRITE,format,1,44100);
    sf_count_t framesWritten = handle.writef(samples, numSamples);
    assert(handle);
    assert(framesWritten==numSamples);
}