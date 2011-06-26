//
//  Perceptron.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <map>
#include <iostream>
#include "constants.h"
#include <vector>

using namespace std;

template <class T>
class Perceptron{
public:
    vector<T>** train(map<vector<T>,InstrumentClass> *m, InstrumentClass *classes, size_t numClasses);
    
    vector<T>*  w(InstrumentClass a, InstrumentClass b, map<vector<T>,InstrumentClass> *m);
    
};