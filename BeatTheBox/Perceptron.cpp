//
//  Perceptron.cpp
//  BeatTheBox
//
//  Created by Mikkel Gravgaard on 14/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Perceptron.h"
#include "ClassificationHelper.h"

MatrixXd* Perceptron::train(map<string, InstrumentClass> *m, InstrumentClass *classes, int numClasses){
    MatrixXd *ws = new MatrixXd[numClasses*numClasses];
//    int nFeatures = ClassificationHelper::getFeatures(new double[]{0,1,2,3,4,5,6,7,8,9,10}).length;

    
    return ws; 
}

MatrixXd* Perceptron::w(InstrumentClass a, InstrumentClass b, map<string, InstrumentClass> *m){
    cout << "training " << a << " versus " << b << endl;
    return 0;
}