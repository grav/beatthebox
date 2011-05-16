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
#include <vector.h>
#include "DSP.h"
#include "LinearAlgebra.h"

#define ITERATIONS 1000000

using namespace std;
using namespace linalg;

vector<double>** Perceptron::train(map<vector<double>, InstrumentClass> *m, InstrumentClass *classes, int numClasses){
    vector<double>** ws = new vector<double>*[numClasses*numClasses];
    for(int a=0; a<numClasses;a++){
        for(int b=0; b<numClasses;b++){
            if(a!=b) ws[a*numClasses+b] = w(classes[a],classes[b],m);
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
            vector<double> *x = extendWithOne((*it).first);
            if(klass==b){
                vector<double> *xM = times(x, -1);
                featuresList.push_back(xM);
            } else {
                featuresList.push_back(x);
            }
        }
    }
    vector<double> *wTemp = randomUnitVector(nFeatures);
    vector<double> *w = extendWithOne(*wTemp);
    delete wTemp;
    for(int i=0;i<ITERATIONS;i++){
        long index = rand() % featuresList.size();
        vector<double> *x = featuresList[index];
        if(dot(x,w)<=0){
            wTemp = add(w, x);
            delete w;
            w = wTemp;
            
        }
        if(i%(ITERATIONS/10)==0){
            cout << "Iteration: " << i << "/" << ITERATIONS << endl;
        }

    }
    return times(w, 1.0/l2norm(w));
}

