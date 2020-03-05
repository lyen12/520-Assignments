#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include <complex.h>
#include "typed_array.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<int> b;
        b.set(0, 6);
        b.set(1, 7);
        b.set(2, 8);
        EXPECT_EQ(b.get(0), 6);
        EXPECT_EQ(b.get(1), 7);
        EXPECT_EQ(b.get(2), 8);
        std::cout << "b is " << b << "\n";


        b.push(3);
        EXPECT_EQ(b.get(3), 3);
        std::cout << "b is " << b << "\n";
        b.push_front(2);
        EXPECT_EQ(b.get(0), 2);
        std::cout << "b is " << b << "\n";


        EXPECT_EQ(b.pop(), 3);
        EXPECT_EQ(b.pop_front(), 2);
        std::cout << "b is " << b << "\n";
        EXPECT_EQ(b.get(0), 6);
        EXPECT_EQ(b.get(2), 8);
        std::cout << "b is " << b << "\n";

        TypedArray<int> c;
        c.push_front(2);
    }

    TEST(TypedArray, Error) {
        try {
            TypedArray<int> c;
            c.pop();
            ASSERT_EQ(true,false);  //Fail safe to ensure prior argument is invalid
        } catch (std::range_error e ) {
        ASSERT_STREQ(e.what(), "Cannot pop from an empty array");
        }
    }

    TEST(TypedArray, Concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a.concat(a).concat(a); // yields a new array [0,1,0,1,0,1]
                                                   // Should leave a untouched.
    }

    TEST(TypedArray, Reverse) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        a.set(2,2);
        a.reverse();
    }

    TEST(TypedArray, Concat_operator) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a; // yields [0,1,0,1,0,1]
    }

    TEST(Complex, Real_Imag) {
        Complex comp = Complex( 2.0, 4.0 );
        double real = comp.real();
        double imaginary = comp.imaginary();
        ASSERT_EQ( real, 2.0 );
        ASSERT_EQ( imaginary, 4.0 );
    }

    TEST(Complex, Conj) {
        Complex comp = Complex( 2.0, 4.0 );
        Complex conj_comp = comp.conjugate();
        ASSERT_EQ( conj_comp.real(), 2.0);
        ASSERT_EQ( conj_comp.imaginary() , -4.0 );
    }

    TEST(Complex, multiply) {
        Complex a = Complex( 2.0, 4.0 );
        Complex mult_a = a * a;
        ASSERT_EQ( mult_a.real(), 4.0 );
        ASSERT_EQ( mult_a.imaginary() , 16.0 );
    }

    TEST(Complex, add) {
        Complex a = Complex( 2.0, 4.0 );
        Complex add_a = a + a;
        ASSERT_EQ( add_a.real(), 4.0 );
        ASSERT_EQ( add_a.imaginary() , 8.0 );
    }

    TEST(Complex, equal) {
        Complex a = Complex( 2.0, 4.0 );
        Complex b = Complex ( 3.0, 6.0 );
        ASSERT_EQ( a == b , false );

    }

}