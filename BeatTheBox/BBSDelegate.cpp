//
//  BBSDelegate.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "BBSDelegate.h"

void BBSDelegate::receiveSegment(double *arr, int length, int onset){
    
}

void BBSDelegate::setClass(int index, InstrumentClass klass){
}

void BBSDelegate::handleDSP(double *sound, double *onsets, double *outputTrack, double *similarTrack, int length, IHostController *hostController){
}

void BBSDelegate::updateSimilarTrack(int index, double *read, int length){
    
}

IClassification* BBSDelegate::getClassification(){
    return 0;
}