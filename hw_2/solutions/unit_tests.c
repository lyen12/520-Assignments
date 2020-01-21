#include "gtest/gtest.h"
#include "solutions.h"

namespace {

    TEST(Point,Basics) {

    //Test for running_total
    int a = 1;
    printf("Input was %d, current total is %d\n", a, running_total(a));

    printf("2nd run, Input was %d, current total is %d\n", a, running_total(a));
    
    }


    TEST(HW2,Reverse) {

    //Test for reverse
    int x[] = {10, 20, 30, 40, 50};
    reverse_in_place (x,5);
    
    }
}
