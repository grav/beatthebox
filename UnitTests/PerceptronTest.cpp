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
using namespace std;

TEST(PerceptronTest,TestIt){
    InstrumentClass classes[] = {BD,SD,HH};
    Perceptron *perceptron = new Perceptron();

    perceptron->train(ClassificationHelper::getFeatureMap("/Users/grav/Desktop/flat.data"),
                     classes, 3);

}