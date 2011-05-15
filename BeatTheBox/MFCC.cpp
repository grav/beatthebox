//
//  MFCC.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "MFCC.h"
#include <stdio.h>

double* MFCC::_H;

int MFCC::_N,MFCC::_M, MFCC::_f_min, MFCC::_f_max;
double MFCC::_deltaPhi, MFCC::_fs;

void MFCC::init(int freqs,int mels, double fs,int minF,int maxF){
    _N=freqs; _M=mels; _fs=fs; _f_min=minF; _f_max=maxF;
    generateTable();
}

void MFCC::init(int spectrumLength) {
    init(spectrumLength, NUM_MELS, 44100, 20, 22050);
}

double MFCC::amplitude(int freq, int mel){
    return _H[freq*_M+mel];
}
double* MFCC::getMFCCs(double* spectrum, int spectrumLength){
    if(!_H || spectrumLength!=_N){
        init(spectrumLength);
    }
    
    for(int i=0;i<spectrumLength;i++){
        assert(spectrum[i]>=0);
    }
    double *mfccs = new double[_M];
    for(int m=0; m<_M; m++){
        double sum = 0;
        for(int n=0; n<_N; n++){
            sum+=_H[n*_M+m] * spectrum[n];
        }
        mfccs[m]=log(1+sum);
    }
    return mfccs;
}

void MFCC::generateTable(){
    _deltaPhi=(phi(_f_max) - phi(_f_min)) / _M+1;
    _H = new double[_N*_M];
    for (int i=0; i<_N;i++){
        for (int j=0; j<_M;j++){
            _H[i*_M+j]=compH(i+1,j+1);
        }
    }
}

double MFCC::phi(int f){
    return (2595 * log10(f/700+1));
}

double MFCC::freq_c(int m){
    return 700*(pow(10,phi_c(m)/2595)-1);
}

double MFCC::freq(int k){
    return k*(_fs/2)/_N;
}

double MFCC::phi_c(int m){
    return m * _deltaPhi;
}

double MFCC::compH(int k, int m){
    double c=0;
    if (freq(k)<freq_c(m-1)){
        c=0;
    } else if ( freq(k) < freq_c(m) && freq(k) >= freq(m-1)){
        c=(freq(k)-freq_c(m-1))/(freq_c(m)-freq_c(m-1));
    } else if ( freq(k) < freq_c(m+1) && freq(k) >= freq_c(m)){
        c=(freq(k)-freq_c(m+1))/(freq_c(m)-freq_c(m+1));      
    } else if (freq(k) >= freq_c(m+1)){
        c=0;
    } else {
        // todo: why do we ever end up here? (with N=32,M=13,fs=44100,minF=20,maxF=20000)
        //			assert(false);
    }
    return c;
}
