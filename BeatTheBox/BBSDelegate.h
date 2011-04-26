//
//  BBSDelegate.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "SegmentOwner.h"

class BBSDelegate : public ISegmentOwner {
public:
    void receiveSegment(double* arr, int length, int onset);
//    void setClass(int index, InstrumentClass klass);
//    IClassification* getClassification();
//    void updateSimilarTrack(int index, double* read, int length);
//    void handleDSP(double* sound, double* onsets, 
//                           double* outputTrack, double* similarTrack,
//                           int length, IHostController *hostController);
    
    
};
