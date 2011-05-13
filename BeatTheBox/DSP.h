//
//  dsp.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "fftw3.h"

class DSP{
public:
    
    static double length(fftw_complex c);
    
    // TODO - enable generic types
    static double foldl(double* arr, int length, double init, double (^f)(double x, double y));
    
    static double* mapWithIndex(double* arr, int length, double (^f)(double x, int i));
                              
    static double* map(double* arr, int length, double (^f)(double x));    

    static double* line(double from, double to, int length);
    
    static double* line(int length);
    
    static double sum(double* arr, int length);
     
    static double rms(double* arr, int length);
    
    static double* hamming(int m);
    
    static void zeroPad(double* arr, int length, int winSize, double *&resultArr, int &resultLength);
    
    static void energyEnvelope(double* arr, int length, int winSize, double *&resultArr, int &resultLength);
    
    static double* copyRange(double* arr, int start, int length);

    static double max(double* arr, int length);
    
    static double* reverse(double* arr, int length);
    
    static int attackTime(double *arr, int length, int k);
    
    static int firstLowPoint(double *arr, int length);
    
    static void printMatlabArray(double *arr, int length);
    
};
