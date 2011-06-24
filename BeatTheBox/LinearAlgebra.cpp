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

    void add(vector<double>* a, vector<double>* b, vector<double> *r){
        assert(a->size()==b->size());
        assert(r->size()==0);
        for(int i=0;i<a->size();i++){
            r->push_back((*a)[i]+(*b)[i]);
        }
    }

    void times(vector<double> *a, double c, vector<double>* r){
        assert(r->size()==0);
        for(int i=0;i<a->size();i++){
            r->push_back((*a)[i]*c);
        }
    }

    double dot(vector<double>* a, vector<double>* b){
        assert(a->size()==b->size());
        double r = 0;
        for(int i=0;i<a->size();i++){
            r+= (*a)[i]*(*b)[i];
        }
        return r;
    }

    void extendWithOne(vector<double> *v, vector<double> *r){
        assert(r->size()==0);
        for(int i=0;i<v->size();i++){
            r->assign(v->begin(),v->end());
        }
        r->push_back(1);
    }

    void randomUnitVector(int length, vector<double>* rNorm){
        vector<double> noise;
        DSP::noise(length,&noise);
        vector<double> r(noise.begin(),noise.begin()+length);
        times(&noise,1.0/l2norm(&r),rNorm);
    }
}