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

class ISegmentOwner; // forward-declaration

class Segment{
private: 
    int _startDelta;
    int _stopDelta;
public:
    Segment(ISegmentOwner& owner, double sr);
    void init();
    int getSegmentStartDelta();
    int getSegmentStopDelta();

    void findSegment(std::vector<double>* signal, int onset, std::vector<double> *&result);
    
    static int getStart(std::vector<double>* arr, int onset, int winSize);
    static int getStop(std::vector<double>* arr, int onset, int winSize);
    
    void pushSample(double s, bool isOnset);
    
    
                        
    std::vector<double>* _signal;
    int _signalLength;
	// current position in the signal
    int _signalPos;
	// index of detected onset of the signal
    int _onset;
    
    // flag signalling whether an onset has ever been detected
	// will be set to and remain true, when the first onset is detected
	bool _onsetDetected;
    ISegmentOwner& _owner;
    
};
