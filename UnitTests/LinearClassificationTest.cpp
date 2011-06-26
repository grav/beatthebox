#include "gtest/gtest.h"
#include "LinearClassification.h"
#include <map>
#include <vector>
#include "ClassificationHelper.h"
#include "SoundHelper.h"
#include "constants.h"

TEST(DISABLED_LinearClassification,HitRate){
    LinearClassification<double> linClas(LINEAR_MODEL_PATH);
    int hits=0;
    int testSize=0;
    std::map<std::string, InstrumentClass> m; 
    ClassificationHelper<double>::getMap(FLAT_FILE_PATH,&m);
    std::map<std::string,InstrumentClass>::iterator it;
    int i=0;
    for(it=m.begin();it!=m.end();it++){
        i++;
        std::cout << "Testing "<<i<<"/"+m.size()<<std::endl;
        InstrumentClass klass = (*it).second;
        if(true || klass){ // todo - only include classes contained in the model
            testSize++;
            std::vector<double> sample;
            std::string path = PATH_PREFIX + (*it).first;
            std::cout << "Reading " << path << std::endl;
            SoundHelper::loadMono(path, &sample);
            hits+= linClas.query(&sample)==klass?1:0;
        }
    }
    double hitrate = (double)hits/(double)testSize;
    std::cout << "hitrate: " << hitrate << std::endl;
    EXPECT_TRUE(hitrate>0.8);

}