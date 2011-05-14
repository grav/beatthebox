//
//  MatTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include <map.h>

using namespace std;

TEST(MatlabTest,Read){

    map<string,InstrumentClass> classes;
    
    FILE *pFile;
    long lSize;
    char *buffer;
    size_t result;

    pFile=fopen("/Users/grav/Desktop/flat.data", "rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
    
    /* the whole file is now loaded in the memory buffer. */
    
    long i=0; // buffer pointer
    int j=0; // fileName pointer
    char fileName[1024];
    while(i<lSize){
        fileName[j]=buffer[i];
        j++;
        if(buffer[i]==0){ // null termination
            // get instrument class
            i++;
            InstrumentClass k = InstrumentClass((int)buffer[i]);
            string s = fileName;
            classes[s]=k;
//            printf("%s: %d\n",fileName,klass);
            j=0; // reset fileName pointer
        }
        i++;
    }
    
    // terminate
    fclose (pFile);
    free (buffer);
    
    EXPECT_EQ(798,classes.size());
    EXPECT_EQ(BD, classes["martin/segments/human4_04.wav"]);
    EXPECT_EQ(SD,classes["session2/segments/mikkel_16_02.wav"]);
}
