//
//  LinearClassification.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Classification.h"
#include <vector.h>
#include "constants.h"
#include <iostream>
#include "LinearModel.h"

class LinearClassification : public IClassification{
public:
    
    ~LinearClassification();
    
    void init(std::string path);
    InstrumentClass query(std::vector<double> *segment);
    InstrumentClass ddag(std::vector<double> *x);
    Classification type();
    LinearModel *_model;

};