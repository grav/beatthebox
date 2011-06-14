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

void LinearClassification::init(std::string path){

    // todo - simply make linearmodel member
    LinearModel m;
    m.load(path);
    _ws=m._ws;
    _classes=m._classes;
    _numClasses=m._numClasses;
}

InstrumentClass LinearClassification::query(std::vector<double> *segment){
    vector<double> *features = ClassificationHelper::getFeatures(segment);
    vector<double> *x = linalg::extendWithOne(*features);
    return ddag(x);
}

InstrumentClass LinearClassification::ddag(std::vector<double> *x){
    int a = _numClasses-1;
    int b = 0;
    while(a!=b){
        vector<double> *w = _ws[a*_numClasses+b];
        if(linalg::dot(x, w)>0){
            b++;
        } else{
            a--;
        }
        // now a==b
    }
    return _classes[a];
}

Classification LinearClassification::type(){
    return LINEAR;
}