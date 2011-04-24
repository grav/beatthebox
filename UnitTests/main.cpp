//
//  main.cpp
//  UnitTests
//
//  Created by Mikkel Gravgaard on 24/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include <iostream>
#include "gtest/gtest.h"
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}