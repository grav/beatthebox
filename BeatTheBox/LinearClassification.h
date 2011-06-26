//
//  LinearClassification.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Classification.h"
#include <vector>
#include "constants.h"
#include <iostream>
#include "LinearModel.h"

class LinearClassification : public IClassification{
public:
    LinearClassification(std::string path);
    ~LinearClassification();
    
    InstrumentClass query(std::vector<double> *segment);
    InstrumentClass ddag(std::vector<double> *x);
    Classification type();
    LinearModel<double> *_model;

};