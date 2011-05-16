//
//  Perceptron.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <map.h>
#include <iostream.h>
#include "constants.h"
#include <vector.h>

using namespace std;

class Perceptron{
public:
    vector<double>** train(map<vector<double>,InstrumentClass> *m, InstrumentClass *classes, int numClasses);
    
    vector<double>*  w(InstrumentClass a, InstrumentClass b, map<vector<double>,InstrumentClass> *m);
    
};