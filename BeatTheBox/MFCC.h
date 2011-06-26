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

template <class T>
class MFCC {
public:
    static T* _H;
    static int _N,_M, _f_min, _f_max;
    static T _deltaPhi, _fs;

    static void init(int freqs,int mels, T fs,int minF,int maxF);    
    static void init(int spectrumLength);
    
    static T amplitude(int freq, int mel);
    static T* getMFCCs(T* spectrum, int spectrumLength);
    
    static void generateTable();
    
    static T phi(int f);
    
    static T freq_c(int m);
    
    static T freq(int k);
    
    static T phi_c(int m);
    
    static T compH(int k, int m);
    
};

