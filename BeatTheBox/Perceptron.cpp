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

#define ITERATIONS 1000000

using namespace std;

double l2norm(vector<double>* v){
    double sum = 0;
    for(int i=0;i<v->size();i++){
        sum+=pow((*v)[i],2);
    }
    return sqrt(sum);
}

vector<double>* add(vector<double>* a, vector<double>* b){
    // todo - stub
    assert(a->size()==b->size());
    vector<double> *r = new vector<double>;
    for(int i=0;i<a->size();i++){
        r->push_back((*a)[i]+(*b)[i]);
    }
    return r;
}

vector<double>* times(vector<double> *a, double c){
    // todo - stub
    vector<double> *r = new vector<double>;
    for(int i=0;i<a->size();i++){
        r->push_back((*a)[i]*c);
    }
    return r;
}

double dot(vector<double>* a, vector<double>* b){
    // todo - stub
    assert(a->size()==b->size());
    double r = 0;
    for(int i=0;i<a->size();i++){
        r+= (*a)[i]+(*b)[i];
    }
    return r;
}

vector<double>* extendWithOne(vector<double> v){
    vector<double> *r = new vector<double>;
    for(int i=0;i<v.size();i++){
        r->push_back(v[i]);
    }
    r->push_back(1);
    return r;
}

vector<double>* randomUnitVector(int length){
    double *noise = DSP::noise(length);
    vector<double> *r = new vector<double>;
    r->assign(noise,noise+length);
    vector<double> *rNorm = times(r,1.0/l2norm(r));
    delete r;
    return rNorm;
}

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

