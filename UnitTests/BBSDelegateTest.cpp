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
#include <iostream>
#include "LinearClassification.h"
#include "SoundHelper.h"
#include "DSP.h"

#define LOOP_SIZE 9
#define AUDIO_BUFFER_SIZE 4
double* makeOnsetsSignal(int sampleLength, int* indexes, int numIndexes);

// util function
double* makeOnsetsSignal(int sampleLength, int* indexes, int numIndexes){
    double *onsets = new double[sampleLength];
    for(int i=0;i<numIndexes;i++){
        onsets[indexes[i]]=1;
    }
    return onsets;
}

TEST(BBSDelegateTest, mockClassification){
    BBSDelegate<double> delegate;
    delegate.setClassification(new ClassificationMock());
    EXPECT_TRUE(delegate.mockClassification());
}

TEST(BBSDelegateTest, InsertSamples){
    IHostController *mock = new HostControllerMock();
    BBSDelegate<double> *delegate = new BBSDelegate<double>();
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
    double *out = new double[AUDIO_BUFFER_SIZE];
    double *sim = new double[AUDIO_BUFFER_SIZE];
    delegate->handleDSP(b, o, out, sim, AUDIO_BUFFER_SIZE, mock);
    EXPECT_EQ(RECORD, delegate->_state);
    EXPECT_EQ(2, delegate->_lastOnsetIndex);
    
    double b2[] = {10,12,14,16};
    double o2[] = {0,1,0,0};
    delegate->handleDSP(b2, o2, out, sim, AUDIO_BUFFER_SIZE, mock);
    EXPECT_EQ(5, delegate->_lastOnsetIndex);

    double b3[] = {18,20,22,24};
    delegate->handleDSP(b3, zeros, out, sim, AUDIO_BUFFER_SIZE, mock);
    
    EXPECT_EQ(PLAYBACK, delegate->_state);

    double e1[] = {0,0,-1,0,0,-1,0,0,0};
    for(int i=0;i<LOOP_SIZE;i++){
        EXPECT_DOUBLE_EQ(e1[i], delegate->_outputSelectorTrack[i]);
    }
    
    double e2[] = {1,0,0,-1};
    for(int i=0;i<AUDIO_BUFFER_SIZE;i++){
        EXPECT_DOUBLE_EQ(e2[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, AUDIO_BUFFER_SIZE, mock);
    EXPECT_EQ(PLAYBACK, delegate->_state);
    
    double e3[] = {0,0,-1,0};
    for(int i=0;i<AUDIO_BUFFER_SIZE;i++){
        EXPECT_EQ(e3[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, AUDIO_BUFFER_SIZE, mock);
    double e4[] = {0,0,0,0};
    for(int i=0;i<AUDIO_BUFFER_SIZE;i++){
        EXPECT_EQ(e4[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, AUDIO_BUFFER_SIZE, mock);
    double e5[] = {-1,0,0,-1};
    for(int i=0;i<AUDIO_BUFFER_SIZE;i++){
        EXPECT_EQ(e5[i], out[i]);
    }
    
    delegate->handleDSP(zeros, zeros, out, sim, AUDIO_BUFFER_SIZE, mock);
    double e6[] = {0,0,0,0};
    for(int i=0;i<AUDIO_BUFFER_SIZE;i++){
        EXPECT_EQ(e6[i], out[i]);
    }
    
    
}

TEST(BBSDelegateTest, WholeSample){
    std::string fileName = PATH_PREFIX+(std::string)"session2/mikkel_02.wav";

    vector<double> soundFile; 
    SoundHelper::loadMono(fileName, &soundFile);
    
    SndfileHandle handle(fileName); // alloc on stack
    sf_count_t numSamples = handle.frames()*handle.channels();
    EXPECT_EQ(122880,numSamples);
    
    vector<double> paddedFile;
    DSP::zeroPad(&soundFile, AUDIO_BUFFER_SIZE, &paddedFile);

    int onsets[] = {
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
    
    double *onsetSignal = makeOnsetsSignal((int)(paddedFile.size()), onsets, numIndexes);
    
    IHostController *mock = new HostControllerMock();
    BBSDelegate<double> *delegate = new BBSDelegate<double>();
    delegate->_runSynchronized=true;
    delegate->initSegment(44100);

    IClassification<double> *lin = new LinearClassification<double>(LINEAR_MODEL_PATH);
    delegate->setClassification(lin);
    delegate->startRecord();
    EXPECT_EQ(RECORD, delegate->_state);
    delegate->setLoopSize((int)(paddedFile.size()));
    for(int i=0;i<paddedFile.size();i+=AUDIO_BUFFER_SIZE){
//        std::cout << i << endl;
        double out[AUDIO_BUFFER_SIZE];
        double similar[AUDIO_BUFFER_SIZE];
        delegate->handleDSP(&(paddedFile.front())+i, 
                            onsetSignal+i,
                            out, 
                            similar, AUDIO_BUFFER_SIZE, mock);
    }
    
    std::vector<InstrumentClass> classes;
    std::vector<int> indexes;
    for(int i=0;i<paddedFile.size();i++){
        if(delegate->_onsetTrack[i]!=0){
            classes.push_back((InstrumentClass)(delegate->_onsetTrack[i]));
            indexes.push_back(i);
        }
    }
    EXPECT_EQ(9, classes.size());
    InstrumentClass correctClasses[] = {
        BD,
        HH,
        SD,
        HH,
        BD,
        BD,
        BD,
        SD,
        HH
    };
    for(int i=0;i<classes.size();i++){
        EXPECT_EQ(correctClasses[i], classes[i]);
    }
}



