//
//  ClassificationHelperTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 12/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include "ClassificationHelper.h"
#include "DSP.h"

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
    int bins = winSize/2+1;
    double *spectrogram;
    int frames;
    ClassificationHelper::getSpectrogram(in, inLength, winSize, spectrogram, frames);
    
    double expected[] = {
        0.90154, 0.47746, 0.04826,
        0.80685, 0.42707, 0.13316,
        1.22375, 0.83092, 0.34787,
        0.34584, 0.06874, 0.06590};
    EXPECT_EQ(4, frames);
    int outLength = ((inLength/winSize)/2 + 1) * frames;
    EXPECT_EQ(12,outLength);
    for(int i=0;i<bins*frames;i++){
        EXPECT_TRUE(abs(expected[i]-spectrogram[i])<0.01);
    }
    
}

TEST(ClassificationHelper,GetMap){
    map<std::string,InstrumentClass> *pClasses;
    pClasses = ClassificationHelper::getMap("/Users/grav/Desktop/flat.data");
    
    EXPECT_EQ(798,pClasses->size());
    EXPECT_EQ(BD, (*pClasses)["martin/segments/human4_04.wav"]);
    EXPECT_EQ(SD,(*pClasses)["session2/segments/mikkel_16_02.wav"]);
}

TEST(ClassificationHelper,GetStats){
    double testArr[] = {1,2,3,1,2,3,1,2,3};
    int numBins = 3;
    double *means; double *vars;
    
    ClassificationHelper::getStats(testArr, 3, 3, 1, 
       ^(double *audio, int audioLength) {
           double *r = new double[1];
           r[0] = ClassificationHelper::spectralCentroid(audio, audioLength);
           return r;
       }, means, vars);
    
    EXPECT_EQ(0,vars[0]);
    EXPECT_EQ(ClassificationHelper::spectralCentroid(DSP::copyRange(testArr,0,numBins),numBins),
              means[0]);
}
