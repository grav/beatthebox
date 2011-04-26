//
//  Segment.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

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

class IHostController{
public: 
    virtual void makeOnset() = 0;
    virtual void restartLoop() = 0;
};

class ISegmentOwner{
public:
    virtual ~ISegmentOwner(){}
    virtual void receiveSegment(double* arr, int length, int onset) = 0;
    virtual void setClass(int index, InstrumentClass klass) = 0;
    virtual IClassification getClassification() = 0;
    virtual void updateSimilarTrack(int index, double* read, int length) = 0;
    virtual void handleDSP(double* sound, double* onsets, 
                           double* outputTrack, double* similarTrack,
                           IHostController hostController) = 0;
};

class Segment{
private: 
    int _startDelta;
    int _stopDelta;
public:
    Segment(ISegmentOwner &owner, double sr);
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
    ISegmentOwner &_owner;
    
};