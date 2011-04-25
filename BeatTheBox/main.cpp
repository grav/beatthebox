//
//  main.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 24/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "DSP.h"

int main (int argc, const char * argv[])
{
    int length = 50;
    DSP::printMatlabArray(DSP::hamming(length),length);
    
}

