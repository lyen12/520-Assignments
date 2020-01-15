#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {

        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };

        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);

        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);

        Fraction c = (Fraction) { 21, 33 };
        EXPECT_EQ(reduce(c).num,7);
        EXPECT_EQ(reduce(c).den,11);

        Fraction d = (Fraction) { 0, 33 };
        EXPECT_EQ(reduce(d).num,0);
        EXPECT_EQ(reduce(d).den,1);

        Fraction e = (Fraction) { 33, 0 };
        EXPECT_EQ(reduce(e).num,1);
        EXPECT_EQ(reduce(e).den,0);

        Fraction f = (Fraction) { 0, 0 };
        EXPECT_EQ(reduce(f).num,0);
        EXPECT_EQ(reduce(f).den,0);

        Fraction g = (Fraction) { 4, -2 };
        EXPECT_EQ(reduce(g).num,-2);
        EXPECT_EQ(reduce(g).den,1);

        Fraction h = (Fraction) { -4, -2 };
        EXPECT_EQ(reduce(h).num,2);
        EXPECT_EQ(reduce(h).den,1);


    }

}
