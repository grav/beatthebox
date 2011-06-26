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

template <class T>
Segment<T>::Segment(ISegmentOwner<T>& owner, double sr) : _owner(owner), _startDelta(0), _stopDelta(0){
    _signalLength = (int)(SECONDS * sr);
    _signal = new vector<T>(_signalLength);
    init();
}

template <class T>
void Segment<T>::init(){
    _signalPos = 0;
    _onsetDetected = false;
}

template <class T>
int Segment<T>::getSegmentStartDelta(){
    return _startDelta;
}

template <class T>
int Segment<T>::getSegmentStopDelta(){
    return _stopDelta;
}

template <class T>
int Segment<T>::getStart(vector<T> *arr, int onset, int winSize){
    vector<T> ee;
    vector<T> v(arr->begin(), arr->begin()+onset);
    DSP::energyEnvelope(&v, winSize, &ee);
    vector<T> reversed;
    DSP::reverse(&ee,&reversed);
    return onset-winSize*DSP::firstLowPoint(&reversed);
}

template <class T>
int Segment<T>::getStop(vector<T> *arr, int onset, int winSize){
    vector<T> ee;
    vector<T> v(arr->begin()+onset, arr->end());
    DSP::energyEnvelope(&v, winSize, &ee);
    return onset+winSize*DSP::firstLowPoint(&ee);    
}

template <class T>
void Segment<T>::findSegment(vector<T> *signal, int onset, vector<T> *result){
    // TODO: make constant somewhere
    int start = getStart(signal, onset, SEGMENT_WINSIZE);
    int stop = getStop(signal, onset,SEGMENT_WINSIZE);
    assert(start<=onset); assert(stop>onset);
    if(start==onset && stop==onset){
        // crude hack: seems our onset detection went wrong ...
        // set onset to initial part of signal and 
        // try again!
        onset = 10;
        start = getStart(signal, onset, SEGMENT_WINSIZE);
        stop = getStop(signal, onset,SEGMENT_WINSIZE);
    }
    _startDelta = onset-start;
    _stopDelta = onset-stop;
    result->assign(signal->begin()+start,signal->begin()+stop+1);
}

template <class T>
void Segment<T>::pushSample(T s, bool isOnset){
    (*_signal)[_signalPos] = s;
    if (isOnset){
        if(!_onsetDetected){
            // special case: first time, an onset is detected
            _onsetDetected=true;
            _onset = _signalPos;
        } else {
            int nextOnset = _signalPos;
            vector<T> v(_signal->begin(),_signal->begin()+nextOnset);
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

template class Segment<double>;
