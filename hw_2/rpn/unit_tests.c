#include "gtest/gtest.h"
#include "rpn.h"

namespace {

    TEST(HW2,RPN_BASICS) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_push(1.0);
        rpn_show();
        rpn_add();
        rpn_show();
        rpn_multiply();
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-1.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_POP_OFF) {
        rpn_init();
        rpn_push(2.0);
        rpn_push(0.5);
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-0.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_NEGATION) {
        rpn_init();
        rpn_push(0.5);
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-0.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_ADDITION) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_add();
        ASSERT_EQ(rpn_pop(),2.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_MULTIPLICATION) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_multiply();
        ASSERT_EQ(rpn_pop(),1.0);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }
    TEST(HW2,RPN_DIVISION) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_div();
        ASSERT_EQ(rpn_pop(),0.25);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_ERRORS) {
        
        rpn_push(0.5);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_pop();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_add();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_multiply();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_div();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_negate();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);                                
        rpn_free();

        rpn_init();
        rpn_pop();
        ASSERT_EQ(rpn_error(), POP_ERROR);
        rpn_free();

        rpn_init();
        rpn_negate();
        ASSERT_EQ(rpn_error(), UNARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_add();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_multiply();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_div();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_push(0);
        rpn_div();
        ASSERT_EQ(rpn_error(), DIVIDE_BY_ZERO_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_add();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_negate();
        rpn_multiply();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();        

    }    

}
