//
//  LinearModel.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <vector>
#include "constants.h"
template <class T>
class LinearModel{
public:
    LinearModel();
    LinearModel(std::string path);
    ~LinearModel();
    
    void save(std::string filename);
    void load(std::string filename);

    std::vector<T> *getW(size_t a, size_t b);
    
    std::vector<T> **_ws;  
    InstrumentClass *_classes;
    size_t _numClasses;
    
};