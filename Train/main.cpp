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
    m->_ws = perceptron->train(ClassificationHelper::getFeatureMap(FLAT_FILE_PATH),
                               classes, numClasses);
    m->_classes = classes;
    m->_numClasses = numClasses;
    m->save(LINEAR_MODEL_PATH);
    return 0;
}

