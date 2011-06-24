//
//  main.cpp
//  Recognizer
//
//  Created by Mikkel Gravgaard on 27/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SoundHelper.h"
#include "LinearClassification.h"
#include <assert.h>
#include <vector>

using namespace std;

int main (int argc, const char * argv[])
{
    assert(argc==2);
    // insert code here...
    std::cout << argv[1] << std::endl;
    std::vector<double> samples;
    SoundHelper::loadMono(argv[1], &samples);
    LinearClassification c(LINEAR_MODEL_PATH);
    InstrumentClass klass = c.query(&samples);
    cout << "Class: " << klass << endl;
    return 0;
}

