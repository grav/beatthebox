//
//  Segment.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "HostController.h"
#include <vector>

#define SEGMENT_WINSIZE 300

template <class T>
class ISegmentOwner; // forward-declaration

template <class T>
class Segment{
private: 
    size_t _startDelta;
    size_t _stopDelta;
public:
    Segment(ISegmentOwner<T>& owner, double sr);
    void init();
    size_t getSegmentStartDelta();
    size_t getSegmentStopDelta();

    void findSegment(std::vector<T>* signal, size_t onset, std::vector<T> *result);
    
    static size_t getStart(std::vector<T>* arr, size_t onset, int winSize);
    static size_t getStop(std::vector<T>* arr, size_t onset, int winSize);
    
    void pushSample(T s, bool isOnset);
    
    
                        
    size_t _signalLength;
    std::vector<T>* _signal;
	// current position in the signal
    size_t _signalPos;
	// index of detected onset of the signal
    size_t _onset;
    
    // flag signalling whether an onset has ever been detected
	// will be set to and remain true, when the first onset is detected
	bool _onsetDetected;
    ISegmentOwner<T>& _owner;
    
};
