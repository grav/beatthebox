//
//  dsp.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

class DSP{
public:
    
    // TODO - enable generic types
    static double foldl(double* arr, int length, double init, double (^f)(double x, double y));
    
    static double* map(double* arr, int length, double (^f)(double x));    

    static double* line(double from, double to, int length);
    
    static double* line(int length);
    
    static double sum(double* arr, int length);
     
    static double rms(double* arr, int length);
    
    static double* hamming(int m);
    
    static void zeroPad(double* arr, int length, int winSize, double *&resultArr, int &resultLength);
    
    static void energyEnvelope(double* arr, int length, int winSize, double *&resultArr, int &resultLength);
    
    static double* copyRange(double* arr, int start, int length);

    static void printMatlabArray(double *arr, int length);

};