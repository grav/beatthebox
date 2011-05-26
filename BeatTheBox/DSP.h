//
//  dsp.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "fftw3.h"
#include "sndfile.hh"
#include <iostream>
#include <math.h>
#include <float.h>
#include <assert.h>

class DSP{
public:
    
    static double length(fftw_complex c){
        return sqrt(pow(c[0],2)+pow(c[1],2));
    }
    
    static double foldl(double* arr, int length, double init, double (^f)(double x, double y)){
        double result = init;
        for(int i=0;i<length;i++){
            result = f(result,arr[i]);
        }
        return result;

    }
    
    static double* mapWithIndex(double* arr, int length, double (^f)(double x, int i)){
        double *result = new double[length];
        for(int i=0; i<length;i++){
            result[i] = f(arr[i], i); // apply f on i'th element of arr
        }
        return result;  

    }
                              
    static double* map(double* arr, int length, double (^f)(double x)){
        return mapWithIndex(arr, length, ^(double x, int i){return f(x);});
    }

    static double* line(double from, double to, int length){
        return mapWithIndex(new double[length], length, ^(double v, int i){return (to-from)/length * i+from;});
    }
    
    static double* line(int length){
        return line(0, length, length);
    }
    
    static double sum(double* arr, int length){
        return foldl(arr, length, 0, ^(double x, double y){return x+y;});
    }
     
    static double rms(double* arr, int length){
        return sqrt(sum(map(arr, length, ^(double x){return pow(x, 2);}),length)/length);
    }
    
    static double* hamming(int m){
        return map(line(m), m, ^(double n){return (0.54-0.46*cos((2*M_PI*n)/(m-1)));});
    }
    
    static double* hamming(double *in, int length){
        double *hamWin = hamming(length);
        // todo - delete hamWin in some way!
        return mapWithIndex(in, length, ^(double x, int i){return x*hamWin[i];});
    }
    
    static void zeroPad(double* arr, int length, int winSize, double *&resultArr, int &resultLength){
        int rest = length % winSize;
        if(rest == 0){
            resultLength = length;
        } else {        
            resultLength = length+(winSize-rest);
        }
        resultArr = mapWithIndex(arr, resultLength, ^(double v, int i){return i<length?v:0;});

    }
    
    static void energyEnvelope(double* arr, int length, int winSize, double *&resultArr, int &resultLength){
        double *paddedArr;
        int paddedLength;    
        zeroPad(arr, length, winSize, paddedArr, paddedLength);
        resultLength = paddedLength/winSize;
        
        resultArr = new double[resultLength];
        for(int i=0;i<resultLength;i++){        
            resultArr[i]=rms(copyRange(paddedArr, i*winSize, winSize),winSize);
        }		

    }
    
    static double* copyRange(double* arr, int start, int length){
        // TODO: since the body of the closure refers directly to arr, it isn't a real mapping?
        return mapWithIndex(arr, length, ^(double x, int i){return arr[start+i];});

    }

    static double max(double* arr, int length){
        return foldl(arr, length, -DBL_MAX, ^(double r, double x){return x>r?x:r;});
    }
    
    static double* reverse(double* arr, int length){
        return mapWithIndex(arr, length, ^(double v, int i){return arr[length-1-i];});
    }
    
    static int attackTime(double *arr, int length, int k){
        //TODO - make winSize constants somewhere
        int winSize = 256;
        double *env;
        int envLength;
        energyEnvelope(arr, length, winSize, env, envLength);
        double max = DSP::max(env,envLength);
        for(int i=0;i<envLength;i++){
            if(env[i]>k*max) return i*winSize;
        }
        return INT_MAX;

    }
    
    static int firstLowPoint(double *arr, int length){
        double t = 0.05; // threshold
        double max = DSP::max(arr,length);
        int minIndex = 0; 
        for(int i=0;i<length;i++){
            if(arr[i]<t*max){
                return i;
            }
            if(arr[i]<arr[minIndex]){
                minIndex=i;
            }
        }
        return minIndex;

    }
    
    static void printMatlabArray(double *arr, int length){
        std::cout << "[";
        for(int i=0;i<length;i++){
            std::cout << arr[i] << " ";
        }
        std::cout << "]";

    }
    
    static double* noise(int length){
        double *r = new double[length];
        return map(r, length, ^(double x){return ((double)rand()/(double)RAND_MAX);});
    }
    
};
