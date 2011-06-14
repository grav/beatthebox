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
#include "SoundHelper.h"
#define SECONDS 10

Segment::Segment(ISegmentOwner& owner, double sr) : _owner(owner), _startDelta(0), _stopDelta(0){
    _signalLength = (int)(SECONDS * sr);
    _signal = new vector<double>(_signalLength);
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

int Segment::getStart(vector<double> *arr, int onset, int winSize){
    vector<double> *ee;
    vector<double> *v = new vector<double>(arr->begin(), arr->begin()+onset);
    DSP::energyEnvelope(v, winSize, ee);
    return onset-winSize*DSP::firstLowPoint(DSP::reverse(ee));
}

int Segment::getStop(vector<double> *arr, int onset, int winSize){
    vector<double> *ee;
    vector<double> *v = new vector<double>(arr->begin()+onset, arr->end());
    DSP::energyEnvelope(v, winSize, ee);
    return onset+winSize*DSP::firstLowPoint(ee);    
}

void Segment::findSegment(vector<double> *signal, int onset, vector<double> *&result){
    // TODO: make constant somewhere
    int start = getStart(signal, onset, SEGMENT_WINSIZE);
    int stop = getStop(signal, onset,SEGMENT_WINSIZE);
    assert(start<=onset); assert(stop>onset);
    if(start==onset && stop==onset){
        // crude hack: seems our onset detection went wrong ...
        // set onset to initial part of signal and 
        // try again!
        onset = 10;
        start = start = getStart(signal, onset, SEGMENT_WINSIZE);
        stop = stop = getStop(signal, onset,SEGMENT_WINSIZE);
    }
    _startDelta = onset-start;
    _stopDelta = onset-stop;
    int resultLength = stop+1-start;
    result = new vector<double>(signal->begin()+start,signal->begin()+start+resultLength);
}

void Segment::pushSample(double s, bool isOnset){
    (*_signal)[_signalPos] = s;
    if (isOnset){
        if(!_onsetDetected){
            // special case: first time, an onset is detected
            _onsetDetected=true;
            _onset = _signalPos;
        } else {
            int nextOnset = _signalPos;
            // todo - maybe allocate on heap?
            vector<double> *v = new vector<double>(_signal->begin(),_signal->begin()+nextOnset);
            _owner.receiveSegment(v,_onset);
            for(int j=_onset;j<=nextOnset;j++){
                (*_signal)[j-_onset]=(*_signal)[j];
            }
            // zero the rest
            for(int i=nextOnset-_onset+1;i<=nextOnset;i++){
                (*_signal)[i]=0;
            }
            _signalPos = nextOnset-_onset;
            _onset = _signalPos;
        }
    }
    _signalPos++;
}
