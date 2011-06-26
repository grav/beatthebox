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

size_t min(size_t a, size_t b);

template <class T>
class BBSDelegate : public ISegmentOwner<T> {
public:
    BBSDelegate();
    ~BBSDelegate();
    /* inherited from ISegmentOwner */
    void receiveSegment(std::vector<T> arr, size_t onset);
    void setClass(size_t index, InstrumentClass klass);
    IClassification<T>* getClassification();
    void updateSimilarTrack(size_t index, T* read, size_t length);
    void handleDSP(T* sound, T* onsets, 
                           T* outputTrack, T* similarTrack,
                           size_t length, IHostController *hostController);
    
    
    void setClassification(IClassification<T> *c);

    void drumDir(char* path);
    
    void startRecord();
    
    void startPlayback();
    
    char* setPath(char* path);

    bool isReady();
    
    void initSegment(T sr);
    
    void setLoopSize(size_t size);
    
    void switchState(size_t arg, size_t inletIndex, IHostController *hostController);

    bool mockClassification();
    
    /* member vars */
    // AsyncClassification &_async;
    bool _runSynchronized;
    // for debugging
    size_t _counter;
    State _state;
    size_t _trackPointer;
    
    // ins
    T *_onsetTrack;
    
    // outs
    T *_similarTrack;
    T *_outputSelectorTrack;
    size_t _loopSize;
    IClassification<T> *_classification;
    size_t _lastOnsetIndex;
    char* _path;
    // todo - init in ctor
    bool _playback;
    Segment<T> *_segment;

};


