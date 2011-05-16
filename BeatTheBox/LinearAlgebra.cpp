//
//  LinearAlgebra.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LinearAlgebra.h"

namespace linalg{
    double l2norm(vector<double>* v){
        double sum = 0;
        for(int i=0;i<v->size();i++){
            sum+=pow((*v)[i],2);
        }
        return sqrt(sum);
    }

    vector<double>* add(vector<double>* a, vector<double>* b){
        assert(a->size()==b->size());
        vector<double> *r = new vector<double>;
        for(int i=0;i<a->size();i++){
            r->push_back((*a)[i]+(*b)[i]);
        }
        return r;
    }

    vector<double>* times(vector<double> *a, double c){
        vector<double> *r = new vector<double>;
        for(int i=0;i<a->size();i++){
            r->push_back((*a)[i]*c);
        }
        return r;
    }

    double dot(vector<double>* a, vector<double>* b){
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
}