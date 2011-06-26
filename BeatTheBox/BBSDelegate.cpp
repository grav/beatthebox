//
//  BBSDelegate.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "BBSDelegate.h"
#include "DSP.h"
#include "Classification.h"
#include <typeinfo>
#include <assert.h>
#include "Segment.h"
#include "SoundHelper.h"

#define BUFFER_SIZE 44100 * 20

//TODO define with macro somewhere
int min(int a, int b){
    return a<b?a:b;
}

BBSDelegate::BBSDelegate(){
    _classification = NULL;
    _outputSelectorTrack = new double[BUFFER_SIZE];
    _onsetTrack = new double[BUFFER_SIZE];
    _similarTrack = new double[BUFFER_SIZE];
    _segment = NULL;

}

BBSDelegate::~BBSDelegate(){
    delete _classification;
    delete[] _outputSelectorTrack;
    delete[] _onsetTrack;
    delete[] _similarTrack;
}

bool BBSDelegate::mockClassification(){
    return _classification->type()==MOCK;
}

void BBSDelegate::receiveSegment(vector<double> arr, int onset){
    vector<double> seg;
    if(mockClassification()){
        seg = arr;
    } else {
        _segment->findSegment(&arr, onset, &seg);

    }
    
    if(_runSynchronized){
        // Single-threaded
        setClass(_lastOnsetIndex, _classification->query(&seg));
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
    _segment->init();
    _state = RECORD;
    _trackPointer = 0;
    _lastOnsetIndex = 0;
    // TODO - delete old refs?
    for(int i=0;i<BUFFER_SIZE;i++){
        _outputSelectorTrack[i]=_onsetTrack[i]=_similarTrack[i]=0;
    }
}

void BBSDelegate::updateSimilarTrack(int index, double *drum, int length){
    int limit = min(index+length, BUFFER_SIZE);
    for (int i = index; i < limit; i++) {
        _similarTrack[i] = drum[i - index];
    }
}

void BBSDelegate::setClassification(IClassification *c){
    delete _classification;
    _classification = c;
}

IClassification* BBSDelegate::getClassification(){
    return _classification;
}

void BBSDelegate::initSegment(double sr){
    delete _segment;
    _segment = new Segment<double>(*this,sr);
    _segment->init();
    _state=HALT;
}

void BBSDelegate::setLoopSize(int size){
    _loopSize = size;
}


