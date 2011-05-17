#include "gtest/gtest.h"
#include "LinearClassification.h"
#include <map.h>
#include "ClassificationHelper.h"
#include "SoundHelper.h"
#include "constants.h"

TEST(LinearClassification,HitRate){
    LinearClassification linClas;
    char *path = (char*)"/Users/grav/Desktop/linearmodel.data"; 
    linClas.init(path);
    int hits=0;
    int testSize=0;
    map<std::string, InstrumentClass> *m = ClassificationHelper::getMap("/Users/grav/Desktop/flat.data");
    map<std::string,InstrumentClass>::iterator it;
    int i=0;
    for(it=m->begin();it!=m->end();it++){
        i++;
        std::cout << "Testing "<<i<<"/"+m->size()<<std::endl;
        InstrumentClass klass = (*it).second;
        if(true || klass){ // todo - only include classes contained in the model
            testSize++;
            double *sample; sf_count_t sampleLength;
            std::string path = PATH_PREFIX + (*it).first;
            std::cout << "Reading " << path << std::endl;
            SoundHelper::loadMono(path, sample, sampleLength);
            hits+= linClas.query(sample, (int)sampleLength)==klass?1:0;
        }
    }
    double hitrate = (double)hits/(double)testSize;
    std::cout << "hitrate: " << hitrate << std::endl;
    EXPECT_TRUE(hitrate>0.8);

}