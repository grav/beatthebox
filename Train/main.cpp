//
//  main.cpp
//  Train
//
//  Created by Mikkel Gravgaard on 14/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LinearModel.h"
#include "Perceptron.h"
#include "ClassificationHelper.h"

int main (int argc, const char * argv[])
{

    InstrumentClass classes[] = {BD,SD,HH};
    int numClasses = 3;
    Perceptron *perceptron = new Perceptron();
    
    LinearModel *m = new LinearModel();
    map<vector<double>,InstrumentClass> featuresMap;
    ClassificationHelper::getFeatureMap(FLAT_FILE_PATH,&featuresMap);
    m->_ws = perceptron->train(&featuresMap,
                               classes, numClasses);
    m->_classes = new InstrumentClass[numClasses];
    for(int i=0;i<numClasses;i++){
        m->_classes[i]=classes[i];
    }
    m->_numClasses = numClasses;
    m->save(LINEAR_MODEL_PATH);
    delete m;
    delete perceptron;
    return 0;
}

