//
//  LinearClassification.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LinearClassification.h"
#include "ClassificationHelper.h"
#include "LinearAlgebra.h"
#include "LinearModel.h"

LinearClassification::LinearClassification(std::string path){
    _model = new LinearModel(path);
    
}

LinearClassification::~LinearClassification(){
    delete _model;
}

InstrumentClass LinearClassification::query(std::vector<double> *segment){
    vector<double> features;
    ClassificationHelper::getFeatures(segment,&features);
    vector<double> x;
    linalg::extendWithOne(&features,&x);
    InstrumentClass result = ddag(&x);
    return result;
}

InstrumentClass LinearClassification::ddag(std::vector<double> *x){
    int a = _model->_numClasses-1;
    int b = 0;
    while(a!=b){
        vector<double> *w = _model->getW(a,b);
        if(linalg::dot(x, w)>0){
            b++;
        } else{
            a--;
        }
        // now a==b
    }
    return _model->_classes[a];
}

Classification LinearClassification::type(){
    return LINEAR;
}