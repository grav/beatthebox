//
//  main.cpp
//  simple
//
//  Created by Mikkel Gravgaard on 23/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <vector>
#include "DSP.h"
int main (int argc, const char * argv[])
{

    // insert code here...
    std::vector<double> *in = new vector<double>;
    in->assign(7, 100);
    std::vector<double> result;
    DSP::zeroPad(in,33,&result);
    std::cout << "Hello, World!\n";
    delete in;
    return 0;
}

