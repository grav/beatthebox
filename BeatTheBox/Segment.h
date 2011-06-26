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
    int _startDelta;
    int _stopDelta;
public:
    Segment(ISegmentOwner<T>& owner, double sr);
    void init();
    int getSegmentStartDelta();
    int getSegmentStopDelta();

    void findSegment(std::vector<T>* signal, int onset, std::vector<T> *result);
    
    static int getStart(std::vector<T>* arr, int onset, int winSize);
    static int getStop(std::vector<T>* arr, int onset, int winSize);
    
    void pushSample(T s, bool isOnset);
    
    
                        
    int _signalLength;
    std::vector<T>* _signal;
	// current position in the signal
    int _signalPos;
	// index of detected onset of the signal
    int _onset;
    
    // flag signalling whether an onset has ever been detected
	// will be set to and remain true, when the first onset is detected
	bool _onsetDetected;
    ISegmentOwner<T>& _owner;
    
};
