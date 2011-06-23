#include "gtest/gtest.h"
#include "LinearAlgebra.h"
#include <vector>

using namespace linalg;
using namespace std;
TEST(LinAlg, l2norm){
    double a[] = {1,2,3,4};
    vector<double> v(a,a+4);
    EXPECT_EQ(sqrt(30),l2norm(&v));
}

TEST(LinAlg,add){
    int length = 4;
    double a[] = {1,2,3,4};
    vector<double> v1(a,a+length);
    double b[] = {0.5, 0.7, -1, -11};
    vector<double> v2(b,b+length);
    double e[] = {1.5, 2.7, 2, -7};
    vector<double> *r = add(&v1,&v2);
    for(int i=0;i<length;i++){
        EXPECT_EQ(e[i],(*r)[i]); 
    }
}

TEST(LinAlg,times){
    int length = 4;
    double a[] = {2.3,1.0,-3,99};
    vector<double> v1(a,a+length);
    double c = 2.5;
    double e[] = {2.3*2.5, 1.0*2.5, -3*2.5, 99*2.5};
    vector<double> *r = times(&v1,c);
    for(int i=0;i<length;i++){
        EXPECT_EQ(e[i],(*r)[i]); 
    }
    
}

TEST(LinAlg, dot){
    int length = 4;
    double a[] = {1,2,3,4};
    vector<double> v1(a,a+length);
    double b[] = {0.5, 0.7, -1, -11};
    vector<double> v2(b,b+length);
    double e = 1*0.5+2*0.7+3*(-1)+4*(-11);
    double r = dot(&v1,&v2);
    EXPECT_EQ(e,r);
}

TEST(LinAlg, extendWithOne){
    int length = 4;
    double a[] = {2.3,1.0,-3,99};
    vector<double> v(a,a+length);
    double e[] = {2.3,1.0,-3,99,1};
    vector<double> ve(e,e+length+1);
    vector<double> *r = extendWithOne(v);
    EXPECT_EQ(ve.size(),v.size()+1);
    for(int i=0;i<length;i++){
        EXPECT_EQ((*r)[i], ve[i]);
    }
    EXPECT_EQ(r->back(), 1);
    
}