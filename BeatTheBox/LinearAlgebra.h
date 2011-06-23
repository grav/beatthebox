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
    vector<double>* add(vector<double>* a, vector<double>* b);
    vector<double>* times(vector<double> *a, double c);
    double dot(vector<double>* a, vector<double>* b);
    vector<double>* extendWithOne(vector<double> v);
    vector<double>* randomUnitVector(int length);


};