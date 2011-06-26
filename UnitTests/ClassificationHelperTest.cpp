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
    EXPECT_EQ(14.0/6.0, ClassificationHelper<double>::spectralCentroid(new vector<double>(test,test+3)));
    
    double test2[] = {1,-1,0};
    EXPECT_EQ(0,ClassificationHelper<double>::spectralCentroid(new vector<double>(test2,test2+3)));
}

TEST(ClassificationHelperTest,Spectrogram){
    double in[] = { 
        0.58893, 0.46418, 0.55557, 0.86521, 
        0.59228, 0.35114, 0.54886, 0.83083, 
        0.47888, 0.56554, 0.97078, 0.03093, 
        0.87661, 0.10419, 0.17629, 0.74675};
    size_t inLength = 16;
    int winSize = 4;
    double *spectrogram;
    size_t frames; int bins;
    ClassificationHelper<double>::getSpectrogram(new vector<double>(in, in+inLength), winSize, spectrogram, frames, bins);
    
    double expected[] = {
        0.90154, 0.47746, 0.04826,
        0.80685, 0.42707, 0.13316,
        1.22375, 0.83092, 0.34787,
        0.34584, 0.06874, 0.06590};
    EXPECT_EQ(4, frames);
    size_t outLength = ((inLength/winSize)/2 + 1) * frames;
    EXPECT_EQ(12,outLength);
    size_t precision = 10000;
    for(size_t i=0;i<bins*frames;i++){
        EXPECT_EQ((expected[i]*precision),(spectrogram[i]*precision));
    }
    
}

TEST(ClassificationHelper,GetMap){
    map<std::string,InstrumentClass> pClasses;
    ClassificationHelper<double>::getMap(FLAT_FILE_PATH,&pClasses);
    
    EXPECT_EQ(798,pClasses.size());
    EXPECT_EQ(BD, pClasses["martin/segments/human4_04.wav"]);
    EXPECT_EQ(SD,pClasses["session2/segments/mikkel_16_02.wav"]);
}

TEST(ClassificationHelper,GetStats){
    double testArr[] = {1,2,3,1,2,3,1,2,3};
    size_t numBins = 3;
    double *means; double *vars;
    
    ClassificationHelper<double>::getStats(testArr, 3, 3, 1, 
       ^(double *audio, size_t audioLength) {
           double *r = new double[1];
           r[0] = ClassificationHelper<double>::spectralCentroid(new vector<double>(audio, audio+audioLength));
           return r;
       }, means, vars);
    
    EXPECT_EQ(0,vars[0]);
    EXPECT_EQ(ClassificationHelper<double>::spectralCentroid(new vector<double>(testArr,testArr+numBins)),
              means[0]);
}

