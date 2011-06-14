//
//  SoundHelper.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "sndfile.hh"
#include "SoundHelper.h"
#include <assert.h>

void makeMono(double *samples, sf_count_t &numSamples);

void SoundHelper::loadMono(std::string fileName, std::vector<double> *&samples){
    SndfileHandle handle(fileName); // alloc on stack
    sf_count_t numSamples = handle.frames()*handle.channels();
    assert(numSamples>0);
    double *samplesArr = new double[(int)numSamples];
    sf_count_t read = handle.read(samplesArr,numSamples);
    samples = new std::vector<double>(samplesArr,samplesArr+numSamples);
    assert(read==numSamples);
    delete[] samplesArr;
}

void SoundHelper::saveMono(std::string fileName, std::vector<double> *samples){
    const int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    SndfileHandle handle(fileName,SFM_WRITE,format,1,44100);
    sf_count_t framesWritten = handle.writef(&(samples->front()), samples->size());
    assert(handle);
    assert(framesWritten==samples->size());
}

void SoundHelper::debug(std::vector<double> *signal){
    SoundHelper::saveMono("/Users/grav/Desktop/debug.wav",signal);
}