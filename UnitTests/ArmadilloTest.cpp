//
//  ArmadilloTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include <armadillo>

using namespace arma;
TEST(ArmadilloTest,equality){
    mat A = mat(2,2);
    mat B = mat(2,2);
    A << 1 << 2 << endr << 3 << 4;
    B << 1 << 2 << endr << 3 << 4;
}