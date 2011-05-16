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

class LinearClassification : public IClassification{
public:
    
    vector<double>* *_ws;
    int _numClasses;
    void init(char* path);
    InstrumentClass *_classes;
    InstrumentClass query(double *segment, int segmentLength);
    InstrumentClass ddag(std::vector<double> *x);
    Classification type();

};