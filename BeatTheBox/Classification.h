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

class IClassification{
public:
    virtual void init(std::string path) = 0;
    virtual InstrumentClass query(double* segment, int length) = 0;
    virtual Classification type() = 0;
};

class ClassificationMock : public IClassification{
    void init(std::string path){}
    InstrumentClass query(double* segment, int length) { return InstrumentClass(NN);};
    Classification type(){
        return MOCK;
    }
};
