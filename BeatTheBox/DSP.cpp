//
//  dsp.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DSP.h"
#include <math.h>

double DSP::foldl(double* arr, int length, double init, double (^f)(double x, double y)){
    double result = init;
    for(int i=0;i<length;i++){
        result = f(result,arr[i]);
    }
    return result;
}

double* DSP::map(double* arr, int length,double (^f)(double x)){
    double *result = new double[length];
    for(int i=0; i<length;i++){
        result[i] = f(arr[i]); // apply f on i'th element of arr
    }
    return result;
}

double* DSP::line(double from, double to, int length){
    double *l = new double[length];
    for(int i=0;i<length;i++){
        l[i] = (to-from)/length * i+from;
    }
    return l;
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
    double *result = DSP::line(m);
    double pi = 3.141;
    return DSP::map(result, m, ^(double n){return (0.54-0.46*cos((2*pi*n)/(m-1)));});
}

