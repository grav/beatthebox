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

template <class T>
LinearClassification<T>::LinearClassification(std::string path){
    _model = new LinearModel<T>(path);
    
}

template <class T>
LinearClassification<T>::~LinearClassification(){
    delete _model;
}

template <class T>
InstrumentClass LinearClassification<T>::query(std::vector<T> *segment){
    vector<T> features;
    ClassificationHelper::getFeatures(segment,&features);
    vector<T> x;
    linalg::extendWithOne(&features,&x);
    InstrumentClass result = ddag(&x);
    return result;
}

template <class T>
InstrumentClass LinearClassification<T>::ddag(std::vector<T> *x){
    int a = _model->_numClasses-1;
    int b = 0;
    while(a!=b){
        vector<T> *w = _model->getW(a,b);
        if(linalg::dot(x, w)>0){
            b++;
        } else{
            a--;
        }
        // now a==b
    }
    return _model->_classes[a];
}

template <class T>
Classification LinearClassification<T>::type(){
    return LINEAR;
}

template class LinearClassification<double>;