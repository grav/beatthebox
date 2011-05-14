//
//  CPPTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include <map.h>
#include "constants.h"

using namespace std;

TEST(CPPTest, Map){
    map<string, InstrumentClass> data;

    data["foo"] = BD;
    EXPECT_EQ(BD, data["foo"]);
    data["bar"] = SD;
    EXPECT_EQ(SD, data["bar"]);
}

TEST(CPPTest,Vector){
    double arr[] = {1,2,3};
    int len=3;
    vector<double> v;
    v.assign(arr, arr+len);
}

