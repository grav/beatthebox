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
#include <limits>

using namespace std;

class DSP{
public:
    
    template <typename T>
    static T foldl(vector<T> *arr, T init, T (^f)(T x, T y)){
        T result = init;
        for(size_t i=0;i<arr->size();i++){
            result = f(result,(*arr)[i]);
        }
        return result;

    }
    template <typename T>
    static void mapWithIndex(vector<T>* arr, T (^f)(T x, size_t i), vector<T>* result){
        result->resize(arr->size());
        for(size_t i=0; i<arr->size();i++){
            (*result)[i] = f((*arr)[i], i); // apply f on i'th element of arr
        }
    }
    
    template <typename T>
    static void map(vector<T>* arr, T (^f)(T x), vector<T>* result){
        mapWithIndex(arr, ^(T x, size_t i){return f(x);},result);
    }

    template <typename T>
    static void line(T from, T to, size_t length, vector<T>* result){
        result->resize(length);
        for(size_t i=0;i<length;i++){
            (*result)[i]=(to-from)/length * i+from;
        }
    }
    
    template <typename T>
    static void line(size_t length,vector<T>* result){
        line((T)0, (T)length,length,result);
    }
    
    template <typename T>
    static T sum(vector<T>* arr){
        return foldl(arr, (T)0, ^(T x, T y){return x+y;});
    }
     
    template <typename T>
    static T rms(vector<T>* arr){
        vector<T> result;
        map(arr, ^(T x){return pow(x, 2);},&result);
        return sqrt(sum(&result)/arr->size());
    }
    
    template <typename T>
    static void hamming(size_t m,vector<T>* result){
        vector<T> l;
        line(m,&l);
        map(&l, ^(T n){return (0.54-0.46*cos((2*M_PI*n)/(m-1)));},result);
    }
    
    template <typename T>
    static void hamming(vector<T> *in, vector<T> *result){
        vector<T> hamWin;
        hamming(in->size(),&hamWin);
        mapWithIndex(in, ^(T x, size_t i){return x*hamWin[i];}, result);
    }
    
    template <typename T>
    static void zeroPad(vector<T>* arr, int winSize, vector<T> *resultArr){
        size_t rest = (arr->size() % winSize);
        size_t resultLength;
        if(rest == 0){
            resultLength = arr->size();
        } else {        
            resultLength = arr->size()+(winSize-rest);
        }
        resultArr->resize(resultLength,0);
        for(size_t i=0;i<arr->size();i++){
            (*resultArr)[i] = (*arr)[i];
        }
    }
    
    template <typename T>
    static void energyEnvelope(vector<T>* arr, int winSize, vector<T> *resultArr){
        vector<T> paddedArr;
        zeroPad(arr, winSize, &paddedArr);
        size_t resultLength = (paddedArr.size()/winSize);

        resultArr->resize(resultLength);
        for(size_t i=0;i<resultLength;i++){        
            vector<T> v(paddedArr.begin()+(i*winSize), 
                             paddedArr.begin()+((i+1)*winSize));
            
            (*resultArr)[i]=rms(&v);
        }		

    }
    
    template <typename T>
    static T max(vector<T>* arr){
        return foldl(arr, -DBL_MAX, ^(T r, T x){return x>r?x:r;});
    }
    
    template <typename T>
    static void reverse(vector<T>* arr, vector<T> *result){
        mapWithIndex(arr, ^(T v, size_t i){return (*arr)[arr->size()-1-i];},result);
    }
    
    template <typename T>
    static size_t attackTime(vector<T> *arr, size_t k){
        //TODO - make winSize constants somewhere
        size_t winSize = 256;
        vector<T> env;
        size_t envLength;
        energyEnvelope(arr, winSize, &env);
        T max = DSP::max(&env);
        for(size_t i=0;i<envLength;i++){
            if(env[i]>k*max) return i*winSize;
        }
        return SIZE_MAX;

    }
    
    template <typename T>
    static size_t firstLowPoint(vector<T> *arr){
        T t = 0.05; // threshold
        T max = DSP::max(arr);
        size_t minIndex = 0; 
        for(size_t i=0;i<arr->size();i++){
            if((*arr)[i]<t*max){
                return i;
            }
            if((*arr)[i]<(*arr)[minIndex]){
                minIndex=i;
            }
        }
        return minIndex;

    }
    
    template <typename T>
    static void prsize_tMatlabArray(T *arr, size_t length){
        std::cout << "[";
        for(size_t i=0;i<length;i++){
            std::cout << arr[i] << " ";
        }
        std::cout << "]";

    }
    
    template <typename T>
    static void noise(size_t length, vector<T> *result){
        result->resize(length);
        map(result, ^(T x){return ((T)rand()/(T)RAND_MAX);},result);
    }
    
};
