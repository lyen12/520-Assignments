#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, Basics) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 };

        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,8);
        Complex z = add(a,b);
        printf("add result %e + %ei\n", z.real, z.im);

        EXPECT_EQ(negate(a).real,-2);
        EXPECT_EQ(negate(a).im,-3);
        EXPECT_EQ(negate(b).real,-4);
        EXPECT_EQ(negate(b).im,-5);
        Complex x = add(a,b);
        printf("negate result %e + %ei\n", x.real, x.im);

        EXPECT_EQ(multiply(a,b).real,-7);
        EXPECT_EQ(multiply(a,b).im,22);
        Complex w = multiply(a,b);
        printf("multiply result %e + %ei\n", w.real, w.im);

        EXPECT_NEAR(magnitude(a),3.60555,.001);
        printf("magnitude of a: %e\n", magnitude(a));
        EXPECT_NEAR(magnitude(b),6.40312,.001);
        printf("magnitude of b: %e\n", magnitude(b));          

         

    }

}
