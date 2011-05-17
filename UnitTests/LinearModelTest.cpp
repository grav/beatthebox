#include "gtest/gtest.h"
#include "LinearModel.h"
#include "Perceptron.h"
#include "ClassificationHelper.h"


TEST(DISABLED_LinearModel, LoadSave){
    InstrumentClass classes[] = {BD,SD,HH};
    int numClasses = 3;
    Perceptron *perceptron = new Perceptron();
    
    LinearModel *m = new LinearModel();
    m->_ws = perceptron->train(ClassificationHelper::getFeatureMap("/Users/grav/Desktop/flat.data"),
                              classes, numClasses);
    m->_classes = classes;
    m->_numClasses = numClasses;
    m->save("/Users/grav/Desktop/linearmodel.data");

    LinearModel *m2 = new LinearModel();
    m2->load("/Users/grav/Desktop/linearmodel.data");
    EXPECT_EQ(m2->_numClasses, m->_numClasses);
    EXPECT_EQ(NULL,m2->_ws[0]);
    std::vector<double> *v1 = m->_ws[1];
    std::vector<double> *v2 = m2->_ws[1];
    EXPECT_EQ(v1->size(), v2->size());
    for(int i=0; i<v1->size(); i++){
        EXPECT_EQ((*v1)[i], (*v2)[i]);
    }
    
    
}

