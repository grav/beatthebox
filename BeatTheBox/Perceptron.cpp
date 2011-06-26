//
//  Perceptron.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Perceptron.h"
#include "ClassificationHelper.h"
#include "constants.h"
#include "MFCC.h"
#include <vector>
#include "DSP.h"
#include "LinearAlgebra.h"

#define ITERATIONS 1000000
using namespace std;
using namespace linalg;

template <class T>
vector<T>** Perceptron<T>::train(map<vector<T>, InstrumentClass> *m, InstrumentClass *classes, size_t numClasses){
    vector<T>** ws = new vector<T>*[numClasses*numClasses];
    for(size_t a=0; a<numClasses;a++){
        for(size_t b=0; b<numClasses;b++){
            size_t i = a*numClasses+b;
            if(a!=b) {
                ws[i] = w(classes[a],classes[b],m);
            } else {
                ws[i] = NULL;
            }
        }
    }
    return ws; 
}

template <class T>
vector<T>* Perceptron<T>::w(InstrumentClass a, InstrumentClass b, map<vector<T>, InstrumentClass> *m){
    cout << "training " << a << " versus " << b << endl;
    size_t nFeatures = NUM_MELS*2;
    vector<vector<T>*> featuresList;
    typename map<vector<T>, InstrumentClass>::iterator it;
    for(it=m->begin(); it!=m->end(); it++){
        InstrumentClass klass = (*it).second;
        if(klass==a || klass==b){
            vector<T> i = (*it).first;
            vector<T> x;
            extendWithOne(&i,&x);
            if(klass==b){
                vector<T> xM;
                times(&x, (T)-1,&xM);
                featuresList.push_back(new vector<T>(xM));
            } else {
                featuresList.push_back(new vector<T>(x));
            }
        }
    }
    vector<T> wTemp; 
    randomUnitVector(nFeatures,&wTemp);
    vector<T> w;
    extendWithOne(&wTemp,&w);
    for(size_t i=0;i<ITERATIONS;i++){
        long index = rand() % featuresList.size();
        vector<T> *x = featuresList[index];
        if(dot(x,&w)<=0){
            vector<T> wTemp;
            add(&w, x,&wTemp);
            w.assign(wTemp.begin(),wTemp.end());
            
        }
        if(i%(ITERATIONS/10)==0){
            cout << "Iteration: " << i << "/" << ITERATIONS << endl;
        }

    }
    vector<T> *result = new vector<T>();
    times(&w, 1.0/l2norm(&w),result);

    // clean up
    for(size_t i=0;i<featuresList.size();i++){
        vector<T> *v = featuresList[i];
        delete v;
    }
    
    return result;
}

template class Perceptron<double>;

