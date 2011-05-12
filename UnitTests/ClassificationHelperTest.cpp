//
//  ClassificationHelperTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "ClassificationHelper.h"

TEST(ClassificationHelperTest,SpectralCentroid){
    double test[] = {1,2,3};
    EXPECT_EQ(14.0/6.0, ClassificationHelper::spectralCentroid(test,3));
    
    double test2[] = {1,-1,0};
    EXPECT_EQ(0,ClassificationHelper::spectralCentroid(test2,3));
}

