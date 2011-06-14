#include "gtest/gtest.h"
#include "LinearModel.h"
#include "Perceptron.h"
#include "ClassificationHelper.h"


TEST(LinearModel, Load){
//    InstrumentClass classes[] = {BD,SD,HH};
    int numClasses = 3;
    int numFeatures = 27;

    LinearModel *m2 = new LinearModel(LINEAR_MODEL_PATH);
    EXPECT_EQ(numClasses, m2->_numClasses);
    EXPECT_EQ(NULL,m2->_ws[0]);
    std::vector<double> *v2 = m2->_ws[1];
    EXPECT_EQ(numFeatures, v2->size());
//    for(int i=0; i<v1->size(); i++){
//        EXPECT_EQ((*v1)[i], (*v2)[i]);
//    }
    
    
}

