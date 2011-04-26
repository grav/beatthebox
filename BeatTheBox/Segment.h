//
//  Segment.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "HostController.h"

enum InstrumentClass{
    BD = 2,
    SD = 3,
    HH = 4,
    NN = -1
};

class IClassification{
public:
    virtual void init(char* path) = 0;
    virtual InstrumentClass query(double* segment, int length) = 0;
};

class ClassificationMock : public IClassification{
    virtual void init(char* path){}
    virtual InstrumentClass query(double* segment, int length) { return InstrumentClass(BD);};
};

class ISegmentOwner{
public:
    virtual ~ISegmentOwner(){}
    virtual void receiveSegment(double* arr, int length, int onset) = 0;
    virtual void setClass(int index, InstrumentClass klass) {};
    virtual IClassification* getClassification() {return new ClassificationMock();};
    virtual void updateSimilarTrack(int index, double* read, int length) {};
    virtual void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           int length, IHostController *hostController) = 0;
};

class Segment{
private: 
    int _startDelta;
    int _stopDelta;
public:
    Segment(ISegmentOwner *owner, double sr);
    void init();
    int getSegmentStartDelta();
    int getSegmentStopDelta();

    void findSegment(double* signal, int length, int onset, double *&result, int &resultLength);
    
    static int getStart(double* arr, int length, int onset, int winSize);
    static int getStop(double* arr, int length, int onset, int winSize);
    
    void pushSample(double s, bool isOnset);
    
    
                        
    double* _signal;
    int _signalLength;
	// current position in the signal
    int _signalPos;
	// index of detected onset of the signal
    int _onset;
    
    // flag signalling whether an onset has ever been detected
	// will be set to and remain true, when the first onset is detected
	bool _onsetDetected;
    ISegmentOwner *_owner;
    
};

class SegmentOwnerMock : public ISegmentOwner{
public:
    void setSegment(Segment *segment){
        // todo - delete old s?
        _s = segment;
    }
    
    void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           int length, IHostController *hostController) {
        for(int i=0;i<length;i++){
            _s->pushSample(sound[i], onsets[i]==1);
        }
    }
    
    void receiveSegment(double* arr, int length, int onset) {
        //TODO: delete old segment?
        _segment = arr;
        _segmentLength = length;
        _onset = onset;
    }
    
    int getLastOnset(){
        return _onset;
    }
    Segment *_s;
    int _onset;
    double* _segment;
    int _segmentLength;
    
};

