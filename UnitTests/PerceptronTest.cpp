//
//  PerceptronTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 15/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "Perceptron.h"
#include <map.h>
#include "ClassificationHelper.h"
#include "LinearModel.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

TEST(DISABLED_PerceptronTest,TestIt){
    InstrumentClass classes[] = {BD,SD,HH};
    Perceptron *perceptron = new Perceptron();

    int numClasses = 3;
    
    perceptron->train(ClassificationHelper::getFeatureMap(FLAT_FILE_PATH),
                                  classes, numClasses);


}