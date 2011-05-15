//
//  FFTW_Test.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 13/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DSP.h"
#include <math.h>
#include "fftw3.h"
#include <assert.h>
#include "SoundHelper.h"
#include "gtest/gtest.h"

#define N 10
#define N2 N / 2 + 1

void printAsMatlab(fftw_complex *arr, int length){
    printf("[");
    for(int i=0;i<length;i++){
        printf("%f + %f%s ", arr[i][0],arr[i][1],"i");
    }
    printf("]\n");
}

TEST(FFTWTest, Test){
    double in[] = {1,2,3,4,5,6,7,8,9,0};
    fftw_complex *out; 
    fftw_plan p; 
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N); 
    p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    fftw_execute(p); 
    
    double amp[N2];
    for(int i=0;i<N2;i++){
        amp[i] = DSP::length(out[i]);
    }
    
    fftw_destroy_plan(p); fftw_free(out);
    
    double expected[] = {45.0000,16.1803,8.5065,6.1803,5.2573,5.0000};
    for(int i=0;i<N2;i++){
        EXPECT_TRUE(abs(expected[i]-amp[i])<0.01);
    }

    
    
}

void foo(int n, double *&spectrogram, int &length){
    int winSize=256;
    int bins = winSize/2+1;
    length = bins*n;
    spectrogram = new double[length];
    
    for(int i=0;i<n;i++){
        double *in = DSP::noise(winSize);
        
        fftw_complex *out;
        fftw_plan p;
        
        out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*winSize);
        p = fftw_plan_dft_r2c_1d(winSize, in, out, FFTW_ESTIMATE);
        
        fftw_execute(p);
        
        
        
        // copy from out to spectrogram
        for(int bin=0;bin<bins;bin++){
            int frame = i/bins;
            spectrogram[frame*bins+bin]=DSP::length(out[bin]);
        }
        
        fftw_destroy_plan(p);
        fftw_free(out);
    }

}

TEST(FFTWTest, free){
    int n = 100000;
    double *spec;
    int length;
    foo(0, spec, length);
}