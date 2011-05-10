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

#define LOOP_SIZE 9
#define BUFFER_SIZE 4

TEST(BBSDelegateTest, mockClassification){
    IHostController *mock = new HostControllerMock();
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
    
}