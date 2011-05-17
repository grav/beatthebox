//
//  SegmentTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "SegmentOwner.h"
#include "DSP.h"
#include "SoundHelper.h"

#define TEST_SIZE 4
#define SAMPLE_RATE 44100

TEST(Segment,GetStart){
    double *sample; sf_count_t length;
    int segmentLength = 19635;
    int onset = 3850;
    int winSize = 300;
    SoundHelper::loadMono("/Users/grav/repositories/uni/feature/session2/mikkel_02.wav", sample, length);
    int start = Segment::getStart(sample, segmentLength, onset, winSize);
    EXPECT_EQ(2350,start);
}

TEST(Segment,GetStop){
    double *sample; sf_count_t length;
    int segmentLength = 19635;
    int onset = 3850;
    int winSize = 300;
    SoundHelper::loadMono("/Users/grav/repositories/uni/feature/session2/mikkel_02.wav", sample, length);
    int stop = Segment::getStop(sample, segmentLength, onset, winSize);
    EXPECT_EQ(14350,stop);
}

TEST(SegmentTest, InsertSamples){
    IHostController *mock = new HostControllerMock();
    double signal[] = {1,2,3,4};
    double zeros[] = {0,0,0,0}; 
    SegmentOwnerMock so = SegmentOwnerMock();
    Segment s(so, SAMPLE_RATE);
    so.setSegment(&s);
    so.handleDSP(signal,zeros,zeros,zeros,TEST_SIZE,mock);
    EXPECT_EQ(TEST_SIZE, s._signalPos);
    
    double signal2[] = {7,9,25,3};
    double onsets2[] = {0,0,1,0};
    so.handleDSP(signal2, onsets2, zeros, zeros, TEST_SIZE, mock);
    EXPECT_EQ(6,s._onset);
    
    double signal3[] = {2,4,6,8};
    double onsets3[] = {0,0,0,1};
    so.handleDSP(signal3, onsets3, zeros, zeros, TEST_SIZE, mock);

    double expected[] = {1, 2, 3, 4, 7, 9, 25, 3, 2, 4, 6};
    
    for(int i=0;i<so._segmentLength;i++){
        EXPECT_EQ(expected[i], so._segment[i]);
    }
    EXPECT_EQ(6,so._onset);
    EXPECT_EQ(5,s._onset);
    
    EXPECT_EQ(6,s._signalPos);

    double expected2[] = {25,3,2,4,6,8,0,0,0,0,0,0,0};
    int expectedLength2 = 13;
    double *actual = DSP::copyRange(s._signal,0,expectedLength2);
    for(int i=0;i<expectedLength2;i++){
        EXPECT_EQ(expected2[i], actual[i]);
    }
    
    // test once again. at first, no new onset
    double signal4[] = {10,12,14,16};
    so.handleDSP(signal4,zeros,zeros,zeros,TEST_SIZE,mock);

    double signal5[] = {18,20,22,24};
    double onsets5[] = {0,1,0,0};
    so.handleDSP(signal5,onsets5,zeros,zeros,TEST_SIZE,mock);
    EXPECT_EQ(5, so._onset);
    double expected3[] = {25, 3, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    double expectedLength3 = 11;
    for(int i=0;i<expectedLength3;i++){
        EXPECT_EQ(expected3[i], so._segment[i]);
    }
}

