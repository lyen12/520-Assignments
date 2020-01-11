#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, Basics) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 };

        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,8);

        EXPECT_EQ(negate(a).real,-2);
        EXPECT_EQ(negate(a).im,-3);
        EXPECT_EQ(negate(b).real,-4);
        EXPECT_EQ(negate(b).im,-5);

        EXPECT_EQ(multiply(a,b).real,-7);
        EXPECT_EQ(multiply(a,b).im,22);

        EXPECT_EQ(magnitude(a),3.60555);
        EXPECT_EQ(magnitude(b),6.40312);

        

         

    }

}
