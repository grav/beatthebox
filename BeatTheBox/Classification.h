//
//  Classification.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#pragma once

#include "constants.h"

class IClassification{
public:
    virtual void init(char* path) = 0;
    virtual InstrumentClass query(double* segment, int length) = 0;
};

class ClassificationMock : public IClassification{
    virtual void init(char* path){}
    virtual InstrumentClass query(double* segment, int length) { return InstrumentClass(BD);};
};
