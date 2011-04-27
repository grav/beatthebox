//
//  BBSDelegate.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "BBSDelegate.h"
#include "DSP.h"
#include <typeinfo>

//TODO define with macro somewhere
int min(int a, int b){
    return a<b?a:b;
}

bool BBSDelegate::mockClassification(){
    return typeid(_classification)==typeid(ClassificationMock);
}

void BBSDelegate::receiveSegment(double *arr, int length, int onset){
    double *seg;
    int segLength;
    if(mockClassification()){
        seg = arr;
        segLength = length;
    } else {
        _segment->findSegment(arr, length, onset, seg, segLength);
    }
    
    if(_runSynchronized){
        // Single-threaded
        if(mockClassification()){
            // for testing
            setClass(_lastOnsetIndex, _classification->query(seg, segLength));
        } else {
            // TODO: use async without multithreading
        }
    } else {
        //TODO: multithreading
    }
}

void BBSDelegate::setClass(int index, InstrumentClass klass){
    //TODO - stub
    
}

void BBSDelegate::handleDSP(double *sound, double *onsets, double *outputTrack, double *similarTrack, int length, IHostController *hostController){
    //TODO - stub
}

void BBSDelegate::updateSimilarTrack(int index, double *drum, int length){
    int limit = min(index+length, _bufferSize);
    for (int i = index; i < limit; i++) {
        _similarTrack[i] = drum[i - index];
    }
}

IClassification* BBSDelegate::getClassification(){
    return 0;
}

