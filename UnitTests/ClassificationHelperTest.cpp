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

TEST(ClassificationHelperTest,Spectrogram){
    double in[] = { 
        0.58893, 0.46418, 0.55557, 0.86521, 
        0.59228, 0.35114, 0.54886, 0.83083, 
        0.47888, 0.56554, 0.97078, 0.03093, 
        0.87661, 0.10419, 0.17629, 0.74675};
    int inLength = 16;
    int winSize = 4;
    double *spectrogram;
    int frames;
    ClassificationHelper::getSpectrogram(in, inLength, winSize, spectrogram, frames);
    double expected[] = {
        0.90154, 0.47746, 0.04826,
        0.80685, 0.42707, 0.13316,
        1.22375, 0.83092, 0.34787,
        0.34584, 0.06874, 0.06590};
    EXPECT_EQ(4, frames);
    for(int i=0;i<16;i++){
        printf("%f ",spectrogram[i]);
    }
    
}
