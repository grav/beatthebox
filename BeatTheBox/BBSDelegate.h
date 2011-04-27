//
//  BBSDelegate.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "SegmentOwner.h"

#define BUFFER_SIZE 44100 * 20;

class BBSDelegate : public ISegmentOwner {
public:
    
    /* inherited from ISegmentOwner */
    void receiveSegment(double* arr, int length, int onset);
    void setClass(int index, InstrumentClass klass);
    IClassification* getClassification();
    void updateSimilarTrack(int index, double* read, int length);
    void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           int length, IHostController *hostController);
    
    
    bool switchClassification(Classification type);

    void drumDir(char* path);
    
    void startRecord();
    
    void startPlayback();
    
    char* setPath(char* path);

    bool isReady();
    
    void initSegment(double sr);
    
    void setLoopSize(int size);
    
    
    void switchState(int arg, int inletIndex, IHostController *hostController);
    
    
    
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
    Segment *_segment;
    
};
