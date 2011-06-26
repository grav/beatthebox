//
//  Classification.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "constants.h"
#include <iostream>
#include <vector>

template <class T>
class IClassification{
public:
    virtual InstrumentClass query(std::vector<T>* segment) = 0;
    virtual Classification type() = 0;
};

class ClassificationMock : public IClassification<double>{
    InstrumentClass query(std::vector<double>* segment) { return InstrumentClass(NN);};
    Classification type(){
        return MOCK;
    }
};
