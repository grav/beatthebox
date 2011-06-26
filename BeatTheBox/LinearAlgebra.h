//
//  LinearAlgebra.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <vector>
#include <math.h>
#include <assert.h>
#include "DSP.h"

namespace linalg{
    template <typename T>
    T l2norm(vector<T>* v){
        T sum = 0;
        for(size_t i=0;i<v->size();i++){
            sum+=pow((*v)[i],2);
        }
        return sqrt(sum);
    }

    template <typename T>
    void add(vector<T>* a, vector<T>* b,vector<T>* r){
        assert(a->size()==b->size());
        assert(r->size()==0);
        for(size_t i=0;i<a->size();i++){
            r->push_back((*a)[i]+(*b)[i]);
        }
    }

    template <typename T>
    void times(vector<T> *a, T c,vector<T>* r){
        assert(r->size()==0);
        for(size_t i=0;i<a->size();i++){
            r->push_back((*a)[i]*c);
        }
    }

    template <typename T>
    T dot(vector<T>* a, vector<T>* b){
        assert(a->size()==b->size());
        T r = 0;
        for(size_t i=0;i<a->size();i++){
            r+= (*a)[i]*(*b)[i];
        }
        return r;
    }

    template <typename T>
    void extendWithOne(vector<T> *v,vector<T>* r){
        assert(r->size()==0);
        for(size_t i=0;i<v->size();i++){
            r->assign(v->begin(),v->end());
        }
        r->push_back(1);
    }

    template <typename T>
    void randomUnitVector(size_t length,vector<T>* r){
        vector<T> noise;
        DSP::noise(length,&noise);
        times(&noise,1.0/l2norm(&noise),r);
    }

};

