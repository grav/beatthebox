//
//  LinearModel.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LinearModel.h"
#include <stdio.h>

LinearModel::LinearModel(std::string path){
    load(path);
}

LinearModel::~LinearModel(){
    delete[] _ws;
    delete[] _classes;
}

std::vector<double> *LinearModel::getW(int a, int b){
    return _ws[a*_numClasses+b];
}

void LinearModel::save(std::string filename){
    FILE *pFile;
    
    pFile=fopen(filename.c_str(), "wb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
    
    /* the whole file is now loaded in the memory buffer. */
    
//     write numclasses \0
//     write classes \0
    fwrite(&_numClasses, sizeof(_numClasses), 1, pFile);
    fwrite(_classes, sizeof(InstrumentClass), _numClasses, pFile);
//     write num features
    std::vector<double> *v = _ws[1];
    long nFeatures = v->size();
    fwrite(&nFeatures, sizeof(nFeatures), 1, pFile);
    //     for each class a in classes
    for(int a=0;a<_numClasses;a++){
        //        for each class b in classes
        for(int b=0; b<_numClasses;b++){
            int index = a*_numClasses+b;
            if(a!=b){
                std::cout << "writing " << index << std::endl;
                v = _ws[index];
                // write whole vector
                fwrite(&(v->front()), sizeof(double), v->size(), pFile);
            }
        }
    }
    
    // terminate
    fclose (pFile);

}

void LinearModel::load(std::string filename){
    FILE *pFile;
    
    pFile=fopen(filename.c_str(), "rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
    
    fread(&_numClasses, sizeof(_numClasses), 1, pFile);
    _classes = new InstrumentClass[_numClasses];
    fread(_classes,sizeof(InstrumentClass), _numClasses, pFile);
    //     write num features
    _ws = new std::vector<double>*[_numClasses*_numClasses];
    long nFeatures;
    fread(&nFeatures, sizeof(nFeatures), 1, pFile);
    //     for each class a in classes
    for(int a=0;a<_numClasses;a++){
        //        for each class b in classes
        for(int b=0; b<_numClasses;b++){
            int index = a*_numClasses+b;
            if(a!=b){
                std::cout << "Reading models ... " << index << std::endl;
                std::vector<double> *v = new std::vector<double>;
                double arr[nFeatures];
                fread(arr, sizeof(double), nFeatures, pFile);
                v->assign(arr, arr+nFeatures);
                _ws[index] = v;
            } else {
                _ws[index] = NULL;
            }
        }
    }
    
    // terminate
    fclose (pFile);

}