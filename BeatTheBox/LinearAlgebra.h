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
    double l2norm(vector<double>* v);  
    void add(vector<double>* a, vector<double>* b,vector<double>* r);
    void times(vector<double> *a, double c,vector<double>* r);
    double dot(vector<double>* a, vector<double>* b);
    void extendWithOne(vector<double> *v,vector<double>* r);
    void randomUnitVector(int length,vector<double>* r);


};