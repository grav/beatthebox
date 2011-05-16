//
//  LinearModel.h
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector.h>
#include "constants.h"
class LinearModel{
public:
    void save(std::string filename);
    void load(std::string filename);
    
    std::vector<double> **_ws;  
    InstrumentClass *_classes;
    int _numClasses;
    
};