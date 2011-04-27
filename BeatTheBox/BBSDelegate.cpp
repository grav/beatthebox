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
    _onsetTrack[index] = klass;
    for (int i = index - _segment->getSegmentStartDelta();
         i <= index + _segment->getSegmentStopDelta();
         i++) {
        _outputSelectorTrack[i] = klass;
    }
}

void BBSDelegate::handleDSP(double *sound, double *onsets, double *outputTrack, double *similarTrack, int length, IHostController *hostController){
    for (int i = 0; i < length; i++) {
        // ignore signal until we have a loop size
        switch (_state) {
            case PLAYBACK:
                outputTrack[i] = _outputSelectorTrack[_trackPointer];
                similarTrack[i] = _similarTrack[_trackPointer];
                if (_onsetTrack[_trackPointer] >= BD) {
                    hostController->makeOnset();
                }
                _trackPointer = _trackPointer + 1;
                if (_trackPointer == _loopSize) {
                    _trackPointer = 0;
                    hostController->restartLoop();
                }
                break;
                
            case HALT:
                // mute
                similarTrack[i] = 0;
                break;
            case RECORD:
                bool isOnset = onsets[i] == 1;
                _segment->pushSample(sound[i], isOnset);
                if (isOnset) {
                    _lastOnsetIndex = _trackPointer;
                }
                // between here, we might receive a classified onset
                _trackPointer = _trackPointer + 1;
                if (_trackPointer >= _loopSize) {
                    hostController->restartLoop();
                    startPlayback();
                }
                // just let input run through
                outputTrack[i] = 1;
                break;
        }
    }
}

void BBSDelegate::startPlayback(){
    _trackPointer = 0;
    _state = PLAYBACK;
    _segment->pushSample(0, true);
}

void BBSDelegate::startRecord(){
    //TODO - stub
}

void BBSDelegate::updateSimilarTrack(int index, double *drum, int length){
    int limit = min(index+length, _bufferSize);
    for (int i = index; i < limit; i++) {
        _similarTrack[i] = drum[i - index];
    }
}

bool BBSDelegate::switchClassification(Classification type){
    //TODO - stub
    return false;
}

IClassification* BBSDelegate::getClassification(){
    //TODO - stub
    return 0;
}

