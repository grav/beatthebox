//
//  dsp.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DSP.h"
#include <iostream>
#include <math.h>

double DSP::foldl(double* arr, int length, double init, double (^f)(double x, double y)){
    double result = init;
    for(int i=0;i<length;i++){
        result = f(result,arr[i]);
    }
    return result;
}

double* DSP::mapWithIndex(double *arr, int length, double (^f)(double x, int i)) {
    double *result = new double[length];
    for(int i=0; i<length;i++){
        result[i] = f(arr[i], i); // apply f on i'th element of arr
    }
    return result;    
}

double* DSP::map(double* arr, int length,double (^f)(double x)){
    return DSP::mapWithIndex(arr, length, ^(double x, int i){return f(x);});
}

double* DSP::line(double from, double to, int length){
    return DSP::mapWithIndex(new double[length], length, ^(double v, int i){return (to-from)/length * i+from;});
}

double* DSP::line(int length){
    return DSP::line(0, length, length);
}

double DSP::sum(double* arr, int length){
    return DSP::foldl(arr, length, 0, ^(double x, double y){return x+y;});
}

double DSP::rms(double* arr, int length){
    return sqrt(DSP::sum(DSP::map(arr, length, ^(double x){return pow(x, 2);}),length)/length);
}

double* DSP::hamming(int m){
    return DSP::map(DSP::line(m), m, ^(double n){return (0.54-0.46*cos((2*M_PI*n)/(m-1)));});
}

void DSP::zeroPad(double* arr, int length, int winSize, double *&resultArr, int &resultLength){
    int rest = length % winSize;
    if(rest == 0){
        resultLength = length;
    } else {        
        resultLength = length+(winSize-rest);
    }
    resultArr = new double[resultLength];
    for(int i=0;i<length;i++){
        resultArr[i]=arr[i];
    }
    for(int i=length;i<resultLength;i++){
        resultArr[i]=0;
    }

}

void DSP::energyEnvelope(double *arr, int length, int winSize, double *&resultArr, int &resultLength){
    double *paddedArr;
    int paddedLength;    
    DSP::zeroPad(arr, length, winSize, paddedArr, paddedLength);
    resultLength = paddedLength/winSize;
    resultArr = new double[resultLength];
    for(int i=0;i<resultLength;i++){        
        resultArr[i]=DSP::rms(DSP::copyRange(paddedArr, i*winSize, winSize),winSize);
    }		
}

double* DSP::copyRange(double* arr, int start, int length){
    double* result = new double[length];
    for(int i=0;i<length;i++){
        result[i]=arr[start+i];
    }
    return result;
}

void DSP::printMatlabArray(double *arr, int length){
    std::cout << "[";
    for(int i=0;i<length;i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "]";
}