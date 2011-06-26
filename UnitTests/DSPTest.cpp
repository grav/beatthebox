//
//  DSPTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 25/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "DSP.h"

TEST(FPTests, foldr){
    double arr[] = {0.4, 0.5, 0.2, 1.3, 0.8};
    size_t length = 5;
    double init = 1;
    double result = DSP::foldl(new vector<double>(arr, arr+length), init, ^(double x, double y){return x+y;});
    EXPECT_EQ(4.2, result);
}

TEST(FPTests, map){
    double arr[] = {10,20,30,40,50,60};
    size_t length = 5;
    vector<double> result; 
    DSP::map(new vector<double>(arr, arr+length), ^(double x){return x/2;},&result);
    double expected[] = {5,10,15,20,25,30};
    EXPECT_EQ(expected[0], result[0]);
    EXPECT_EQ(expected[4], result[4]);
}

TEST(DSPTests, line){
    double expected[] = {0,1,2,3,4,5};
    size_t length = 6;
    vector<double> actual;
    DSP::line(length,&actual);
    for(size_t i = 0;i<length;i++){
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(DSPTests, zeroPad){
    double test[] = {1,2,3,4};
    size_t length = 4;
    vector<double> actual;
    int winSize = 3;
    vector<double> v = vector<double>(test, test+length);
    DSP::zeroPad(&v, winSize, &actual);
    
    double expected[] = {1,2,3,4,0,0};
    size_t expectedLength = 6;
    EXPECT_EQ(expectedLength,actual.size());

    for(size_t i=0;i<expectedLength;i++){
        EXPECT_EQ(expected[i], actual[i]);
    }
    
}

TEST(DSPTests,energyEnvelope){
    double x[] ={ 
        0.70605, 0.03183, 0.27692, 0.04617, 
        0.09713, 0.82346, 0.69483, 0.31710, 0.95022, 
        0.03445, 0.43874, 0.38156, 0.76552, 0.79520, 
        0.18687, 0.48976, 0.44559, 0.64631, 0.70936, 
        0.75469, 0.27603, 0.67970, 0.65510, 0.16261, 
        0.11900, 0.49836, 0.95974, 0.34039, 0.58527, 
        0.22381, 0.75127, 0.25510, 0.50596, 0.69908, 
        0.89090, 0.95929, 0.54722, 0.13862, 0.14929, 
        0.25751, 0.84072, 0.25428, 0.81428, 0.24352, 
        0.92926, 0.34998, 0.19660, 0.25108, 0.61604, 
        0.47329, 0.35166, 0.83083, 0.58526, 0.54972, 
        0.91719, 0.28584, 0.75720, 0.75373, 0.38045,
        0.56782, 0.07585, 0.05395, 0.53080, 0.77917,};
    size_t xLength = 12*5+4;
    
    double e[] = { 
        0.38024, 0.56366, 0.55727, 0.61097, 
        0.64981, 0.49844, 0.56998, 0.50550, 
        0.78400, 0.31908, 0.61111, 0.52147, 
        0.59528, 0.62603, 0.63416, 0.47369};
    size_t eLength = 4*4;
    
    int winSize = 4;
    
    vector<double> actual;
    vector<double> in(x, x+xLength);
    DSP::energyEnvelope(&in,winSize,&actual);

    EXPECT_EQ(eLength,actual.size());
    
    size_t precision = 10000;
    for(size_t i=0;i<eLength;i++){
        EXPECT_EQ((e[i]*precision), (actual[i]*precision));
    }
    
}

TEST(DSPTests,max){
    double arr[] = {2,3,0.23,4,1,23.98,0.03,11,0};
    size_t l = 9;
    EXPECT_EQ(23.98, DSP::max(new vector<double>(arr,arr+l)));
}

TEST(DSPTests, reverse_even){
    double arr[] = {2,3};
    double exp[] = {3,2};
    size_t length = 2;
    vector<double> result; 
    DSP::reverse(new vector<double>(arr,arr+length),&result);
    for(size_t i=0;i<length;i++){
        EXPECT_EQ(exp[i], result[i]);
    }
}

TEST(DSPTests,hamming){
    double arr[] = {1,2,3};
    size_t length = 3;
    vector<double> win;
    DSP::hamming(new vector<double>(arr,arr+length),&win);
    double expected[] = {0.0800,2.0000,0.2400};
    size_t precision = 1000;
    for(size_t i=0;i<length;i++){
        EXPECT_EQ((expected[i]*precision), (win[i]*precision));
    }

}

TEST(DSPTests, reverse_uneven){
    double arr[] = {2,3,1};
    double exp[] = {1,3,2};
    size_t length = 3;
    vector<double> result;
    DSP::reverse(new vector<double>(arr,arr+length),&result);
    for(size_t i=0;i<length;i++){
        EXPECT_EQ(exp[i], result[i]);
    }
}

TEST(DSPTests, firstLowPoint){
    double x[] = {78,34,3,67,0,8};
    size_t length = 6;
    EXPECT_EQ(2, DSP::firstLowPoint(new vector<double>(x, x+length)));
    
    double y[] = {3,4,4,5,4,3,4,5,2,4};
    length = 10;
    EXPECT_DOUBLE_EQ(8, DSP::firstLowPoint(new vector<double>(y, y+length)));
}