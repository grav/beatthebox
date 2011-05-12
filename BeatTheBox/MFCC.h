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

class MFCC {
public:
    static double* _H;
    static int _N,_M, _f_min, _f_max;
    static double _deltaPhi, _fs;

    static void init(int freqs,int mels, int fs,int minF,int maxF){
        _N=freqs; _M=mels; _fs=fs; _f_min=minF; _f_max=maxF;
        generateTable();
    }
    
    static void init(int spectrumLength) {
        init(spectrumLength, 13, 44100, 20, 22050);
    }
    
    static double amplitude(int freq, int mel){
        return _H[mel*_M+freq];
    }
    static double* getMFCCs(double* spectrum, int spectrumLength){
        if(!_H){
            init(spectrumLength);
        }
        assert(spectrumLength==_N);
        for(int i=0;i<spectrumLength;i++){
            assert(spectrum[i]>=0);
        }
        double *mfccs = new double[_M];
		for(int m=0; m<_M; m++){
			double sum = 0;
			for(int n=0; n<_N; n++){
				sum+=_H[m*_M+n] * spectrum[n];
			}
			mfccs[m]=log(1+sum);
		}
		return mfccs;
    }
    
    static void generateTable(){
        _deltaPhi=(phi(_f_max) - phi(_f_min)) / _M+1;
		_H = new double[_N*_M];
		for (int i=0; i<_N;i++){
			for (int j=0; j<_M;j++){
				_H[j*_M+i]=compH(i+1,j+1);
			}
		}

    }
    
    static double phi(int f){
		return (2595 * log10(f/700+1));
    }
    
    static double freq_c(int m){
		return 700*(pow(10,phi_c(m)/2595)-1);
    }
    
    static double freq(int k){
		return k*(_fs/2)/_N;
    }
    
    static double phi_c(int m){
		return m * _deltaPhi;
    }
    
    static double compH(int k, int m){
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
    
};

