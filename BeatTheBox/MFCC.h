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
    static size_t _N,_M, _f_min, _f_max;
    static T _deltaPhi, _fs;

    static void init(size_t freqs,size_t mels, T fs,size_t minF,size_t maxF);    
    static void init(size_t spectrumLength);
    
    static T amplitude(size_t freq, size_t mel);
    static T* getMFCCs(T* spectrum, size_t spectrumLength);
    
    static void generateTable();
    
    static T phi(size_t f);
    
    static T freq_c(size_t m);
    
    static T freq(size_t k);
    
    static T phi_c(size_t m);
    
    static T compH(size_t k, size_t m);
    
};

