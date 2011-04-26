//
//  Segment.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Segment.h"
#include "SegmentOwner.h"
#include "DSP.h"
#include <assert.h>
#define SECONDS 10

Segment::Segment(ISegmentOwner *owner, double sr){
    _signalLength = (int)(SECONDS * sr);
    _signal = new double[_signalLength];
    _owner = owner;
    init();
}

void Segment::init(){
    _signalPos = 0;
    _onsetDetected = false;
}

int Segment::getSegmentStartDelta(){
    return _startDelta;
}

int Segment::getSegmentStopDelta(){
    return _stopDelta;
}

int Segment::getStart(double *arr, int length, int onset, int winSize){
    double *ee;
    int eeLength = 0;
    DSP::energyEnvelope(arr, length, winSize, ee, eeLength);
    return onset+winSize*DSP::firstLowPoint(DSP::reverse(ee,eeLength), eeLength);
}

int Segment::getStop(double *arr, int length, int onset, int winSize){
    double *ee;
    int eeLength = 0;
    DSP::energyEnvelope(arr, length, winSize, ee, eeLength);
    return onset+winSize*DSP::firstLowPoint(ee, eeLength);    
}

void Segment::findSegment(double *signal, int length, int onset, double *&result, int &resultLength){
    // TODO: make constant somewhere
    int winSize = 300;
    int start = getStart(signal, length, onset, winSize);
    int stop = getStop(signal, length, onset,winSize);
    assert(start<=onset); assert(stop>onset);
    if(start==onset && stop==onset){
        // crude hack: seems our onset detection went wrong ...
        // set onset to initial part of signal and 
        // try again!
        onset = 10;
        start = start = getStart(signal, length, onset, winSize);
        stop = stop = getStop(signal, length, onset,winSize);
    }
    _startDelta = onset-start;
    _stopDelta = onset-stop;
    resultLength = stop+1-start;
    result = DSP::copyRange(signal, start, resultLength);
}

void Segment::pushSample(double s, bool isOnset){
    _signal[_signalPos] = s;
    if (isOnset){
        if(!_onsetDetected){
            // special case: first time, an onset is detected
            _onsetDetected=true;
            _onset = _signalPos;
        } else {
            int nextOnset = _signalPos;
            _owner->receiveSegment(DSP::copyRange(_signal, 0, nextOnset), nextOnset, _onset);
            for(int j=_onset;j<=nextOnset;j++){
                _signal[j-_onset]=_signal[j];
            }
            // zero the rest
            for(int i=nextOnset-_onset+1;i<=nextOnset;i++){
                _signal[i]=0;
            }
            _signalPos = nextOnset-_onset;
            _onset = _signalPos;
        }
    }
    _signalPos++;
}
