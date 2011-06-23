#include "gtest/gtest.h"
#include <vector>

#define VEC vector<T>

using namespace std;

template <typename T>
T foo(T a){
    return a+1;
}

template <typename T>
T bar(VEC v){
    return v[0]+10;
}

TEST(Generics, Foo){
    float f = 1;
    EXPECT_EQ(2,foo(f));
    double d = 1;
    EXPECT_EQ(2,foo(d));
    
    double a[] = {1,2,3};
    vector<double> v(a,a+3);
    EXPECT_EQ(11, bar(v));
    
}

