//
//  BBSDelegate.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "SegmentOwner.h"
#include <vector>

#define MAX_BUFFER_SIZE 44100 * 20;

int min(int a, int b);

template <class T>
class BBSDelegate : public ISegmentOwner<T> {
public:
    BBSDelegate();
    ~BBSDelegate();
    /* inherited from ISegmentOwner */
    void receiveSegment(std::vector<T> arr, int onset);
    void setClass(int index, InstrumentClass klass);
    IClassification<T>* getClassification();
    void updateSimilarTrack(int index, T* read, int length);
    void handleDSP(T* sound, T* onsets, 
                           T* outputTrack, T* similarTrack,
                           int length, IHostController *hostController);
    
    
    void setClassification(IClassification<T> *c);

    void drumDir(char* path);
    
    void startRecord();
    
    void startPlayback();
    
    char* setPath(char* path);

    bool isReady();
    
    void initSegment(T sr);
    
    void setLoopSize(int size);
    
    void switchState(int arg, int inletIndex, IHostController *hostController);

    bool mockClassification();
    
    /* member vars */
    // AsyncClassification &_async;
    bool _runSynchronized;
    // for debugging
    int _counter;
    State _state;
    int _trackPointer;
    
    // ins
    T *_onsetTrack;
    
    // outs
    T *_similarTrack;
    T *_outputSelectorTrack;
    int _loopSize;
    IClassification<T> *_classification;
    int _lastOnsetIndex;
    char* _path;
    // todo - init in ctor
    bool _playback;
    Segment<T> *_segment;

};


