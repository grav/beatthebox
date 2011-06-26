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
    size_t length = 4;
    double a[] = {1,2,3,4};
    vector<double> v1(a,a+length);
    double b[] = {0.5, 0.7, -1, -11};
    vector<double> v2(b,b+length);
    double e[] = {1.5, 2.7, 2, -7};
    vector<double> r;
    add(&v1,&v2,&r);
    for(size_t i=0;i<length;i++){
        EXPECT_EQ(e[i],r[i]); 
    }
}

TEST(LinAlg,times){
    size_t length = 4;
    double a[] = {2.3,1.0,-3,99};
    vector<double> v1(a,a+length);
    double c = 2.5;
    double e[] = {2.3*2.5, 1.0*2.5, -3*2.5, 99*2.5};
    vector<double> r;
    times(&v1,c,&r);
    for(size_t i=0;i<length;i++){
        EXPECT_EQ(e[i],r[i]); 
    }
    
}

TEST(LinAlg, dot){
    size_t length = 4;
    double a[] = {1,2,3,4};
    vector<double> v1(a,a+length);
    double b[] = {0.5, 0.7, -1, -11};
    vector<double> v2(b,b+length);
    double e = 1*0.5+2*0.7+3*(-1)+4*(-11);
    double r = dot(&v1,&v2);
    EXPECT_EQ(e,r);
}

TEST(LinAlg, extendWithOne){
    size_t length = 4;
    double a[] = {2.3,1.0,-3,99};
    vector<double> v(a,a+length);
    double e[] = {2.3,1.0,-3,99,1};
    vector<double> ve(e,e+length+1);
    vector<double> r;
    extendWithOne(&v,&r);
    EXPECT_EQ(ve.size(),v.size()+1);
    for(size_t i=0;i<length;i++){
        EXPECT_EQ(r[i], ve[i]);
    }
    EXPECT_EQ(r.back(), 1);
    
}

TEST(LinAlg, randomUnitVector){
    vector<double> v;
    size_t n=10;
    randomUnitVector(n,&v);
    EXPECT_EQ(n,v.size());
    size_t precision = 1000;
    EXPECT_EQ(precision, precision*(l2norm(&v)));
}
