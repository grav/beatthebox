//
//  MFCC.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include <assert.h>
#include <math.h>
#define NUM_MELS 13


class MFCC {
public:
    static double* _H;
    static int _N,_M, _f_min, _f_max;
    static double _deltaPhi, _fs;

    static void init(int freqs,int mels, double fs,int minF,int maxF);    
    static void init(int spectrumLength);
    
    static double amplitude(int freq, int mel);
    static double* getMFCCs(double* spectrum, int spectrumLength);
    
    static void generateTable();
    
    static double phi(int f);
    
    static double freq_c(int m);
    
    static double freq(int k);
    
    static double phi_c(int m);
    
    static double compH(int k, int m);
    
};

