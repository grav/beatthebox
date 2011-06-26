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

class BBSDelegate : public ISegmentOwner<double> {
public:
    BBSDelegate();
    ~BBSDelegate();
    /* inherited from ISegmentOwner */
    void receiveSegment(std::vector<double> arr, int onset);
    void setClass(int index, InstrumentClass klass);
    IClassification* getClassification();
    void updateSimilarTrack(int index, double* read, int length);
    void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           int length, IHostController *hostController);
    
    
    void setClassification(IClassification *c);

    void drumDir(char* path);
    
    void startRecord();
    
    void startPlayback();
    
    char* setPath(char* path);

    bool isReady();
    
    void initSegment(double sr);
    
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
    double *_onsetTrack;
    
    // outs
    double *_similarTrack;
    double *_outputSelectorTrack;
    int _loopSize;
    IClassification *_classification;
    int _lastOnsetIndex;
    char* _path;
    // todo - init in ctor
    bool _playback;
    Segment<double> *_segment;

};


