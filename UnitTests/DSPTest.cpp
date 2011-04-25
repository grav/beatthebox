//
//  DSPTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "DSP.h"

TEST(FPTests, Fold){
    double arr[] = {0.4, 0.5, 0.2, 1.3, 0.8};
    int length = 5;
    int init = 1;
    double result = DSP::foldl(arr, length, init, ^(double x,double y){return x+y;});
    
    EXPECT_DOUBLE_EQ(4.2, result);
}

TEST(FPTests, Map){
    double arr[] = {10,20,30,40,50,60};
    int length = 5;
    double *result = DSP::map(arr, length, ^(double x){return x/2;});
    double expected[] = {5,10,15,20,25,30};
    EXPECT_DOUBLE_EQ(expected[0], result[0]);
    EXPECT_DOUBLE_EQ(expected[4], result[4]);
}

TEST(FPTests, Line){
    double expected[] = {0,1,2,3,4,5};
    int length = 6;
    double *actual = DSP::line(length);
    for(int i = 0;i<length;i++){
        EXPECT_DOUBLE_EQ(expected[i], actual[i]);
    }
}