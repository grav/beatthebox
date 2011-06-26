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
    virtual void receiveSegment(std::vector<T> arr, size_t onset) = 0;
    virtual void setClass(size_t index, InstrumentClass klass) {};
    virtual IClassification<T>* getClassification() {return new ClassificationMock();};
    virtual void updateSimilarTrack(size_t index, T* read, size_t length) {};
    virtual void handleDSP(T* sound, T* onsets, 
                           T* outputTrack, T* similarTrack,
                           size_t length, IHostController *hostController) = 0;
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
                   size_t length, IHostController *hostController) {
        for(size_t i=0;i<length;i++){
            _s->pushSample(sound[i], onsets[i]==1);
        }
    }
    
    void receiveSegment(std::vector<T> arr, size_t onset) {
        //TODO: delete old segment?
        delete _segment;
        _segment = new std::vector<T>(arr);
        _onset = onset;
    }
    
    size_t getLastOnset(){
        return _onset;
    }
    Segment<T> *_s;
    size_t _onset;
    std::vector<T>* _segment;
    
};
