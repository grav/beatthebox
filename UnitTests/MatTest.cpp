//
//  MatTest.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "gtest/gtest.h"
#include <stdio.h>

TEST(MatlabTest,Read){

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
            int klass = (int)buffer[i];
            printf("%s: %d\n",fileName,klass);
            j=0; // reset fileName pointer
        }
        i++;
    }
    
    // terminate
    fclose (pFile);
    free (buffer);
}
