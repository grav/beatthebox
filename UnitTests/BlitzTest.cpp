//
//  BlitzTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include <blitz/array.h>
using namespace blitz;
TEST(BlitzTest,SimpleExample){
    Array<int,2> A(3,3), B(3,3), C(3,3), EXPECTED(3,3), DIFF(3,3);
    A = 
    1, 0, 0,
    2, 2, 2,
    1, 0, 0;
    
    B = 
    0, 0, 7,
    0, 8, 0,
    9, 9, 9;
    
    C = A + B;
    
    EXPECTED = 
    1, 0, 7,
    2, 10, 2,
    10, 9, 9;

    DIFF = C-EXPECTED;
    
//    std::cout << DIFF;
    
}