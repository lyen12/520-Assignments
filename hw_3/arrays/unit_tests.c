#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {
    TEST(DynamicArray, count) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        printf("Array a is----->\n");
        DynamicArray_print_debug_info( a );

        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        printf("Array b is----->\n");
        DynamicArray_print_debug_info( b );

        DynamicArray * c = DynamicArray_concat(a, b);
        printf("Array a and b concated is, c----->\n");
        DynamicArray_print_debug_info( c );

        printf("# of arrays are %d\n", DynamicArray_num_arrays() );

        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);
    }

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_STREQ(
            DynamicArray_to_string(da),
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         
    /*TEST for EXERCISE 1*/
    TEST(DynamicArray, Math) {
        DynamicArray * t = DynamicArray_new();
        double s = 1.0;
        for ( int i = 0; i < 5; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 1.0;
        }
        DynamicArray_set(t, 0, 4);
        DynamicArray_set(t, 1, 3);
        DynamicArray_set(t, 2, 7);
        DynamicArray_set(t, 3, 3);
        DynamicArray_set(t, 4, 9);
        DynamicArray_print_debug_info( t ); 

        double array_min = DynamicArray_min ( t );
        double array_max = DynamicArray_max ( t );
        double array_sum = DynamicArray_sum ( t );
        double array_mean = DynamicArray_mean( t );
        double array_median = DynamicArray_median( t );
        ASSERT_EQ(array_min, 3);
        ASSERT_EQ(array_max, 9);
        ASSERT_EQ(array_sum, 26);
        ASSERT_EQ(array_mean, 5.2);
        ASSERT_EQ(array_median, 4);
        printf("Min of array is %e\n", array_min);
        printf("Max of array is %e\n", array_max);
        printf("Sum of array is %e\n", array_sum);
        printf("Mean of inputted array is %e\n", array_mean);
        printf("Median of inputted array is %e\n", array_median);
        DynamicArray_destroy(t);    
        free(t);
    }        
    /*TEST for EXERCISE 2*/
    TEST(DynamicArray, First_and_Last) {
        DynamicArray * t = DynamicArray_new();
        double s = 1.0;
        for ( int i = 0; i < 5; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 1.0;
        }
        DynamicArray_print_debug_info( t ); 
        printf("First element is %e\n", DynamicArray_first(t));
        printf("Last element is %e\n", DynamicArray_last(t));
        DynamicArray_destroy(t);  
        free(t);  
    }
    /*TEST for EXERCISE 3*/
    TEST(DynamicArray, copy) {
        DynamicArray * t = DynamicArray_new();
        double s = 1.0;
        for ( int i = 0; i < 5; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 1.0;
        }
        printf("Current array is:\n");
        DynamicArray_print_debug_info( t ); 

        DynamicArray * new_t = DynamicArray_copy(t);
        printf("Copy of array is:\n");
        DynamicArray_print_debug_info( new_t ); 
        DynamicArray_destroy(t);
        free(t);
        DynamicArray_destroy(new_t);
        free(new_t);
    }

    /*TEST for EXERCISE 4*/
    TEST(DynamicArray, range) {
        DynamicArray * t = DynamicArray_range(5, 6, 0.5);
        DynamicArray_print_debug_info( t ); 
        DynamicArray_destroy(t);
        free(t);
    }

    /*TEST for EXERCISE 5*/
    TEST(DynamicArray, concat) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.5);
        DynamicArray * b = DynamicArray_range(1.0, 2, 0.5);
        printf("Array a is----->\n");
        DynamicArray_print_debug_info( a ); 
        printf("Array b is----->\n");
        DynamicArray_print_debug_info( b ); 

        DynamicArray * c = DynamicArray_concat(a, b); 
        printf("Array c is----->\n");
        DynamicArray_print_debug_info( c ); 

        DynamicArray_destroy(a);
        free(a);
        DynamicArray_destroy(b);
        free(b);
        DynamicArray_destroy(c);
        free(c);
    }

    /*TEST for EXERCISE 6*/
    TEST(DynamicArray, take) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        printf("Array a is----->\n");
        DynamicArray_print_debug_info( a );

        DynamicArray * b = DynamicArray_take(a, 2);  /* yields [ 1, 2 ] */
        printf("Array b is----->\n");
        DynamicArray_print_debug_info( b );

        DynamicArray * c = DynamicArray_take(a, -2); /* yields [ 4, 5 ] */
        printf("Array c is----->\n");
        DynamicArray_print_debug_info( c );

        DynamicArray * d = DynamicArray_take(a, -7);  /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */
        printf("Array d is----->\n");
        DynamicArray_print_debug_info( d );

        DynamicArray_destroy(a);
        free(a);
        DynamicArray_destroy(b);
        free(b);
        DynamicArray_destroy(c);
        free(c);
        DynamicArray_destroy(d);
        free(d);
        
    }
    /*TEST for EXERCISE 7***************************************************/
    /*Comment out other tests before running the TEST below to prevent DynamicArray_num_arrays 
    from counting arrays created from previous tests.*/
    // TEST(DynamicArray, trackanddestroy ) {
    //     DynamicArray * a = DynamicArray_range(0, 1, 0.1);
    //     DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
    //     DynamicArray * c = DynamicArray_concat(a, b);
    //     ASSERT_EQ(DynamicArray_is_valid(a), 1);

    //     ASSERT_EQ(DynamicArray_num_arrays(), 3);
    //     int number_of_arrays = DynamicArray_num_arrays();
    //     int number_of_arrays_destroyed = DynamicArray_destroy_all();
    //     printf("number of arrays is %d\n", number_of_arrays);
    //     printf("number of arrays destroyed is %d\n", number_of_arrays_destroyed);

    //     ASSERT_EQ(number_of_arrays, number_of_arrays_destroyed);
    //     ASSERT_EQ(DynamicArray_is_valid(a), 0);
    //     ASSERT_EQ(DynamicArray_num_arrays(), 0);
    //     free(a);
    //     free(b);
    //     free(c);
    // }

}