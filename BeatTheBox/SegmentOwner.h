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

class ISegmentOwner{
public:
    virtual ~ISegmentOwner(){}
    virtual void receiveSegment(std::vector<double> arr, int onset) = 0;
    virtual void setClass(int index, InstrumentClass klass) {};
    virtual IClassification* getClassification() {return new ClassificationMock();};
    virtual void updateSimilarTrack(int index, double* read, int length) {};
    virtual void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           int length, IHostController *hostController) = 0;
};

class SegmentOwnerMock : public ISegmentOwner{
public:
    void setSegment(Segment<double> *segment){
        // todo - delete old s?
        _s = segment;
    }
    
    void handleDSP(double* sound, double* onsets, 
                   double* outputTrack, double* similarTrack,
                   int length, IHostController *hostController) {
        for(int i=0;i<length;i++){
            _s->pushSample(sound[i], onsets[i]==1);
        }
    }
    
    void receiveSegment(std::vector<double> arr, int onset) {
        //TODO: delete old segment?
        delete _segment;
        _segment = new std::vector<double>(arr);
        _onset = onset;
    }
    
    int getLastOnset(){
        return _onset;
    }
    Segment<double> *_s;
    int _onset;
    std::vector<double>* _segment;
    
};
