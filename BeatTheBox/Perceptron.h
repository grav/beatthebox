//
//  Perceptron.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <Eigen/Dense>
#include <map.h>
#include <iostream.h>
#include "constants.h"
using Eigen::MatrixXd;
using namespace std;

class Perceptron{
public:
    MatrixXd* train(map<string,InstrumentClass> *m, InstrumentClass *classes, int numClasses);
    
    MatrixXd* w(InstrumentClass a, InstrumentClass b, map<string,InstrumentClass> *m);
    
};