//
//  MFCCTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "MFCC.h"

TEST(MFCCTest, TestTable){
    MFCC<double>::init(256, 13, 44100, 20, 20000);
    EXPECT_TRUE(abs(0.9811-MFCC<double>::amplitude(99, 9))<0.03);
    EXPECT_TRUE(abs(0.5576-MFCC<double>::amplitude(49, 7))<0.03);

    int mels = 13;
    int specLength = 32;
    MFCC<double>::init(specLength,mels,44100,20,20000);
    
    double spec[] = {
        32.4056, 0.5630,1.6819,3.1184,
        0.8436,2.6568,0.9034,2.7676,
        2.9607,3.4174,2.0998,2.5051,
        0.5668,0.9690,3.1684,3.1280,
        1.3635,1.1544,1.8269,1.3269,
        2.0960,1.5097,1.9460,0.5690,
        2.4633,2.9193,2.9774,0.9978,
        3.3850,1.4741,2.2922,1.3362};

    double expected[] = {
        0,2.6048,0,0.3806,0.7971,1.3360,0.9431,
        1.4173,2.1748,2.0165,2.2876,2.4428,2.6870};
    
    double * mfccs = MFCC<double>::getMFCCs(spec, specLength);
    
    for(int i=0;i<mels;i++){
        EXPECT_TRUE(abs(mfccs[i]-expected[i])<0.03);
    }
    
}