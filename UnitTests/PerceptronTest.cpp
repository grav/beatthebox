//
//  PerceptronTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 15/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "Perceptron.h"
#include <map>
#include "ClassificationHelper.h"
#include "LinearModel.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

TEST(DISABLED_PerceptronTest,TestIt){
    InstrumentClass classes[] = {BD,SD,HH};
    Perceptron<double> *perceptron = new Perceptron<double>();

    int numClasses = 3;
    std::map<std::vector<double>,InstrumentClass> featuresMap;
    ClassificationHelper<double>::getFeatureMap(FLAT_FILE_PATH,&featuresMap);
    perceptron->train(&featuresMap,classes, numClasses);
}