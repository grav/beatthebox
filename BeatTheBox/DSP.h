//
//  dsp.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <iostream>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <vector>

using namespace std;

class DSP{
public:
    
    static double foldl(vector<double> *arr, double init, double (^f)(double x, double y)){
        double result = init;
        for(int i=0;i<arr->size();i++){
            result = f(result,(*arr)[i]);
        }
        return result;

    }
    
    static vector<double>* mapWithIndex(vector<double>* arr, double (^f)(double x, int i)){
        vector<double> *result = new vector<double>(arr->size());
        for(int i=0; i<arr->size();i++){
            (*result)[i] = f((*arr)[i], i); // apply f on i'th element of arr
        }
        return result;  

    }
                              
    static vector<double>* map(vector<double>* arr, double (^f)(double x)){
        return mapWithIndex(arr, ^(double x, int i){return f(x);});
    }

    static vector<double>* line(double from, double to, int length){
        return mapWithIndex(new vector<double>(length), ^(double v, int i){return (to-from)/length * i+from;});
    }
    
    static vector<double>* line(int length){
        return line(0, (double)length,length);
    }
    
    static double sum(vector<double>* arr){
        return foldl(arr, 0, ^(double x, double y){return x+y;});
    }
     
    static double rms(vector<double>* arr){
        return sqrt(sum(map(arr, ^(double x){return pow(x, 2);}))/arr->size());
    }
    
    static vector<double>* hamming(int m){
        return map(line(m), ^(double n){return (0.54-0.46*cos((2*M_PI*n)/(m-1)));});
    }
    
    static vector<double>* hamming(vector<double> *in){
        vector<double> *hamWin = hamming((int)in->size());
        vector<double> *result = mapWithIndex(in, ^(double x, int i){return x*(*hamWin)[i];});
        delete hamWin;
        return result;
    }
    
    static void zeroPad(vector<double>* arr, int winSize, vector<double> *resultArr){
        int rest = (int)(arr->size() % winSize);
        int resultLength;
        if(rest == 0){
            resultLength = (int)arr->size();
        } else {        
            resultLength = (int)arr->size()+(winSize-rest);
        }
        resultArr->resize(resultLength);
        for(int i=0;i<arr->size();i++){
            (*resultArr)[i] = (*arr)[i];
        }
    }
    
    static void energyEnvelope(vector<double>* arr, int winSize, vector<double> *&resultArr){
        vector<double> paddedArr;
        zeroPad(arr, winSize, &paddedArr);
        int resultLength = (int)(paddedArr.size()/winSize);

        resultArr = new vector<double>(resultLength);
        for(int i=0;i<resultLength;i++){        
            vector<double> v(paddedArr.begin()+(i*winSize), 
                             paddedArr.begin()+((i+1)*winSize));
            
            (*resultArr)[i]=rms(&v);
        }		

    }
    
    static double* copyRange(double* arr, int start, int length){
        // TODO: since the body of the closure refers directly to arr, it isn't a real mapping?
        double *result = new double[length];
        for(int i=0;i<length;i++){
            result[i]=arr[start+i];
        }
        return result;

    }

    static double max(vector<double>* arr){
        return foldl(arr, -DBL_MAX, ^(double r, double x){return x>r?x:r;});
    }
    
    static vector<double>* reverse(vector<double>* arr){
        return mapWithIndex(arr, ^(double v, int i){return (*arr)[arr->size()-1-i];});
    }
    
    static int attackTime(vector<double> *arr, int k){
        //TODO - make winSize constants somewhere
        int winSize = 256;
        vector<double> *env;
        int envLength;
        energyEnvelope(arr, winSize, env);
        double max = DSP::max(env);
        for(int i=0;i<envLength;i++){
            if((*env)[i]>k*max) return i*winSize;
        }
        return INT_MAX;

    }
    
    static int firstLowPoint(vector<double> *arr){
        double t = 0.05; // threshold
        double max = DSP::max(arr);
        int minIndex = 0; 
        for(int i=0;i<arr->size();i++){
            if((*arr)[i]<t*max){
                return i;
            }
            if((*arr)[i]<(*arr)[minIndex]){
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
    
    static void noise(int length, vector<double> *result){
        result->resize(length);
        map(result, ^(double x){return ((double)rand()/(double)RAND_MAX);});
    }
    
};
