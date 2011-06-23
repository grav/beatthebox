//
//  main.cpp
//  MemTest
//
//  Created by Mikkel Gravgaard on 14/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LinearClassification.h"
#include <map>
#include "ClassificationHelper.h"
#include "SoundHelper.h"
#include "constants.h"
#include <iostream>

int main (int argc, const char * argv[])
{

    LinearClassification linClas(LINEAR_MODEL_PATH);
    int hits=0;
    int testSize=0;
    map<std::string, InstrumentClass> *m = ClassificationHelper::getMap(FLAT_FILE_PATH);
    map<std::string,InstrumentClass>::iterator it;
    int i=0;
    int N = 10;
    int size = N*(int)m->size();
    for(int k=0;k<N;k++){
        for(it=m->begin();it!=m->end();it++){
            i++;
            std::cout << "Testing "<<i<<" of " << size <<std::endl;
            InstrumentClass klass = (*it).second;
            if(true || klass){ // todo - only include classes contained in the model
                testSize++;
                vector<double> *sample;
                std::string path = PATH_PREFIX + (*it).first;
                std::cout << "Reading " << path << std::endl;
                SoundHelper::loadMono(path, sample);
                hits+= linClas.query(sample)==klass?1:0;
                delete sample;
            }
        }
    }
    double hitrate = (double)hits/(double)testSize;
    std::cout << "hitrate: " << hitrate << std::endl;
}

