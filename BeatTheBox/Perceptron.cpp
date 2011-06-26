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

vector<double>** Perceptron::train(map<vector<double>, InstrumentClass> *m, InstrumentClass *classes, int numClasses){
    vector<double>** ws = new vector<double>*[numClasses*numClasses];
    for(int a=0; a<numClasses;a++){
        for(int b=0; b<numClasses;b++){
            int i = a*numClasses+b;
            if(a!=b) {
                ws[i] = w(classes[a],classes[b],m);
            } else {
                ws[i] = NULL;
            }
        }
    }
    return ws; 
}

vector<double>* Perceptron::w(InstrumentClass a, InstrumentClass b, map<vector<double>, InstrumentClass> *m){
    cout << "training " << a << " versus " << b << endl;
    int nFeatures = NUM_MELS*2;
    vector<vector<double>*> featuresList;
    map<vector<double>, InstrumentClass>::iterator it;
    for(it=m->begin(); it!=m->end(); it++){
        InstrumentClass klass = (*it).second;
        if(klass==a || klass==b){
            vector<double> i = (*it).first;
            vector<double> x;
            extendWithOne(&i,&x);
            if(klass==b){
                vector<double> xM;
                times(&x, (double)-1,&xM);
                featuresList.push_back(new vector<double>(xM));
            } else {
                featuresList.push_back(new vector<double>(x));
            }
        }
    }
    vector<double> wTemp; 
    randomUnitVector(nFeatures,&wTemp);
    vector<double> w;
    extendWithOne(&wTemp,&w);
    for(int i=0;i<ITERATIONS;i++){
        long index = rand() % featuresList.size();
        vector<double> *x = featuresList[index];
        if(dot(x,&w)<=0){
            vector<double> wTemp;
            add(&w, x,&wTemp);
            w.assign(wTemp.begin(),wTemp.end());
            
        }
        if(i%(ITERATIONS/10)==0){
            cout << "Iteration: " << i << "/" << ITERATIONS << endl;
        }

    }
    vector<double> *result = new vector<double>();
    times(&w, 1.0/l2norm(&w),result);

    // clean up
    for(int i=0;i<featuresList.size();i++){
        vector<double> *v = featuresList[i];
        delete v;
    }
    
    return result;
}

