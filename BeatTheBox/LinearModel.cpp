//
//  LinearModel.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LinearModel.h"
#include <string>
#include <iostream>
template <class T>
LinearModel<T>::LinearModel(){
}

template <class T>
LinearModel<T>::LinearModel(std::string path){
    load(path);
}

template <class T>
LinearModel<T>::~LinearModel(){
    delete[] _ws;
    delete[] _classes;
}

template <class T>
std::vector<T> *LinearModel<T>::getW(size_t a, size_t b){
    return _ws[a*_numClasses+b];
}

template <class T>
void LinearModel<T>::save(std::string filename){
    FILE *pFile;
    
    pFile=fopen(filename.c_str(), "wb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
    
    /* the whole file is now loaded in the memory buffer. */
    
//     write numclasses \0
//     write classes \0
    fwrite(&_numClasses, sizeof(_numClasses), 1, pFile);
    fwrite(_classes, sizeof(InstrumentClass), _numClasses, pFile);
//     write num features
    std::vector<T> *v = _ws[1];
    long nFeatures = v->size();
    fwrite(&nFeatures, sizeof(nFeatures), 1, pFile);
    //     for each class a in classes
    for(size_t a=0;a<_numClasses;a++){
        //        for each class b in classes
        for(size_t b=0; b<_numClasses;b++){
            size_t index = a*_numClasses+b;
            if(a!=b){
                std::cout << "writing " << index << std::endl;
                v = _ws[index];
                // write whole vector
                fwrite(&(v->front()), sizeof(T), v->size(), pFile);
            }
        }
    }
    
    // terminate
    fclose (pFile);

}

template <class T>
void LinearModel<T>::load(std::string filename){
    FILE *pFile;
    
    pFile=fopen(filename.c_str(), "rb");
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
    
    fread(&_numClasses, sizeof(_numClasses), 1, pFile);
    _classes = new InstrumentClass[_numClasses];
    fread(_classes,sizeof(InstrumentClass), _numClasses, pFile);
    //     write num features
    _ws = new std::vector<T>*[_numClasses*_numClasses];
    long nFeatures;
    fread(&nFeatures, sizeof(nFeatures), 1, pFile);
    //     for each class a in classes
    for(size_t a=0;a<_numClasses;a++){
        //        for each class b in classes
        for(size_t b=0; b<_numClasses;b++){
            size_t index = a*_numClasses+b;
            if(a!=b){
                std::cout << "Reading models ... " << index << std::endl;
                std::vector<T> *v = new std::vector<T>;
                T arr[nFeatures];
                fread(arr, sizeof(T), nFeatures, pFile);
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

template class LinearModel<double>;