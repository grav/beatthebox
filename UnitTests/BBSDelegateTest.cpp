//
//  BBSDelegateTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 04/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "HostController.h"
#include "BBSDelegate.h"
#include "Classification.h"
#include "sndfile.hh"
#include <iostream.h>

#define LOOP_SIZE 9
#define BUFFER_SIZE 4

// util function
double* makeOnsetsSignal(int sampleLength, int* indexes, int numIndexes){
    double *onsets = new double[sampleLength];
    for(int i=0;i<numIndexes;i++){
        onsets[indexes[i]]=1;
    }
    return onsets;
}

TEST(BBSDelegateTest, mockClassification){
    BBSDelegate *delegate = new BBSDelegate();
    delegate->setClassification(new ClassificationMock());
    EXPECT_TRUE(delegate->mockClassification());
}

TEST(BBSDelegateTest, InsertSamples){
    IHostController *mock = new HostControllerMock();
    BBSDelegate *delegate = new BBSDelegate();
    delegate->_runSynchronized=true;
    delegate->setClassification(new ClassificationMock());
    
    delegate->initSegment(44100);
    EXPECT_EQ(HALT, delegate->_state);
    
    delegate->setLoopSize(LOOP_SIZE);
    
    delegate->startRecord();
    
    EXPECT_EQ(RECORD, delegate->_state);
    
    // sample: 2 4 6 8 10 12 14 16 18 
    // onsets: 0 0 1 0 0  1  0  0  0
    
    double zeros[] = {0,0,0,0};

    double b[] = {2,4,6,8};
    double o[] = {0,0,1,0};
    double *out = new double[BUFFER_SIZE];
    double *sim = new double[BUFFER_SIZE];
    delegate->handleDSP(b, o, out, sim, BUFFER_SIZE, mock);
    EXPECT_EQ(RECORD, delegate->_state);
    EXPECT_EQ(2, delegate->_lastOnsetIndex);
    
    double b2[] = {10,12,14,16};
    double o2[] = {0,1,0,0};
    delegate->handleDSP(b2, o2, out, sim, BUFFER_SIZE, mock);
    EXPECT_EQ(5, delegate->_lastOnsetIndex);

    double b3[] = {18,20,22,24};
    delegate->handleDSP(b3, zeros, out, sim, BUFFER_SIZE, mock);
    
    EXPECT_EQ(PLAYBACK, delegate->_state);

    // TODO - THESE FAIL
    double e1[] = {0,0,-1,0,0,-1,0,0,0};
    for(int i=0;i<LOOP_SIZE;i++){
        EXPECT_DOUBLE_EQ(e1[i], delegate->_outputSelectorTrack[i]);
    }
    
    double e2[] = {1,0,0,-1};
    for(int i=0;i<BUFFER_SIZE;i++){
        EXPECT_DOUBLE_EQ(e2[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, BUFFER_SIZE, mock);
    EXPECT_EQ(PLAYBACK, delegate->_state);
    
    double e3[] = {0,0,-1,0};
    for(int i=0;i<BUFFER_SIZE;i++){
        EXPECT_EQ(e3[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, BUFFER_SIZE, mock);
    double e4[] = {0,0,0,0};
    for(int i=0;i<BUFFER_SIZE;i++){
        EXPECT_EQ(e4[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, BUFFER_SIZE, mock);
    double e5[] = {-1,0,0,-1};
    for(int i=0;i<BUFFER_SIZE;i++){
        EXPECT_EQ(e5[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, BUFFER_SIZE, mock);
    double e6[] = {0,0,0,0};
    for(int i=0;i<BUFFER_SIZE;i++){
        EXPECT_EQ(e6[i], out[i]);
    }
    
    
}

TEST(BBSDelegateTest, WholeSample){
    std::string fileName = "/Users/grav/repositories/uni/feature/session2/mikkel_02.wav";

    SndfileHandle handle(fileName); // alloc on stack
    sf_count_t numSamples = handle.frames()*handle.channels();
    EXPECT_EQ(122880,numSamples);
    
    sf_count_t paddedLength = numSamples + BUFFER_SIZE-(numSamples % BUFFER_SIZE);
    
    double samples[paddedLength];
    for(sf_count_t i=0;i<paddedLength;i++){
        samples[i]=0;
    }
    sf_count_t read = handle.read(samples,numSamples);
    EXPECT_EQ(numSamples,read);
    
    int indexes[] = {
        3850,
        19635,
        33880,
        48510,
        58135,
        62755,
        78155,
        93555,
        108955
    };
    
    int numIndexes = 9;
    
    double *onsetSignal = makeOnsetsSignal((int)paddedLength, indexes, numIndexes);
    
    IHostController *mock = new HostControllerMock();
    BBSDelegate *delegate = new BBSDelegate();
    delegate->_runSynchronized=true;
    
}

