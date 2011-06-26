//
//  SegmentOwner.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "Classification.h"
#include "Segment.h"
#include <vector>

template <class T>
class ISegmentOwner{
public:
    virtual ~ISegmentOwner(){}
    virtual void receiveSegment(std::vector<T> arr, int onset) = 0;
    virtual void setClass(int index, InstrumentClass klass) {};
    virtual IClassification<T>* getClassification() {return new ClassificationMock();};
    virtual void updateSimilarTrack(int index, T* read, int length) {};
    virtual void handleDSP(T* sound, T* onsets, 
                           T* outputTrack, T* similarTrack,
                           int length, IHostController *hostController) = 0;
};

template <class T>
class SegmentOwnerMock : public ISegmentOwner<T>{
public:
    void setSegment(Segment<T> *segment){
        // todo - delete old s?
        _s = segment;
    }
    
    void handleDSP(T* sound, T* onsets, 
                   T* outputTrack, T* similarTrack,
                   int length, IHostController *hostController) {
        for(int i=0;i<length;i++){
            _s->pushSample(sound[i], onsets[i]==1);
        }
    }
    
    void receiveSegment(std::vector<T> arr, int onset) {
        //TODO: delete old segment?
        delete _segment;
        _segment = new std::vector<T>(arr);
        _onset = onset;
    }
    
    int getLastOnset(){
        return _onset;
    }
    Segment<T> *_s;
    int _onset;
    std::vector<T>* _segment;
    
};
