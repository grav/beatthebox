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

template <class T>
class LinearClassification : public IClassification<T>{
public:
    LinearClassification(std::string path);
    ~LinearClassification();
    
    InstrumentClass query(std::vector<T> *segment);
    InstrumentClass ddag(std::vector<T> *x);
    Classification type();
    LinearModel<T> *_model;

};