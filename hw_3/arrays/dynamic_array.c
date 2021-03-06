#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

/*Global variable for track arrays*/
DynamicArray * first_array = NULL;
DynamicArray * last_array = NULL;
int number_of_arrays_allocated = 0;

void DynamicArray_track ( DynamicArray * a );

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {
    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    DynamicArray_track ( da );
    return da;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    //double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    double value = DynamicArray_last( da );
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    //double value = DynamicArray_get(da, 0);
    double value = DynamicArray_first( da );
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray( const DynamicArray * da, int a, int b) {
    assert(da->buffer != NULL);
    assert(b >= a);
    DynamicArray * result = DynamicArray_new();
    for (int i=a; i<b; i++) {
        DynamicArray_push(result,DynamicArray_get(da, i));
    }
    return result;
    }

/*Exercise 1***************************************************************/
double DynamicArray_min ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double min = INFINITY;
    for ( int i = da->origin; i < da->end; i++) {
        double current_element_value = da->buffer[i];
        if ( min > current_element_value ) {
            min = current_element_value;
        } 
    }
    return min;
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double max = -INFINITY;
    for ( int i = da->origin; i < da->end; i++) {
        double current_element_value = da->buffer[i];
        if ( max < current_element_value ) {
            max = current_element_value;
        } 
    }
    return max;
}
double DynamicArray_mean ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return DynamicArray_sum(da) / DynamicArray_size(da);
}

/*Function for qsort function to be used in DynamicArray_copy_and_sort function.
Compares the doubles in the array*/
int compar_doubles (const void * one, const void * two) {
    const double * one_double = (const double *)one;    //Recasting one as a Double type
    const double * two_double = (const double *)two;    //Recasting two as a Double type
    if (*one_double > *two_double) { return 1;}
    else if (*one_double < *two_double) { return -1;}
    return 0;
}
/*Function to show qsorted array for troubleshooting*/
void array_show(double *a, int size) {
    printf("sorted array is--->");
    for ( int i=0; i<size; i++ ) {
        printf("  %lf", a[i]);
    }
    printf("<---\n");
}
/*Function for Dynamic_median. Function will copy the inputted array and sort it.*/
double *DynamicArray_copy_and_sort( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    int num_of_elements = DynamicArray_size(da);
    int element_byte_size = sizeof(double);
    /*Create an extra array variable the same size as the buffer array*/
    double *sorted_array = (double *)malloc(num_of_elements*element_byte_size);
    /*Copy values from inputted array into new array variable*/
    for ( int i = 0; i < num_of_elements; i++) {
        sorted_array[i] = da->buffer[index_to_offset(da,i)];
    }
    qsort(sorted_array, num_of_elements, element_byte_size, compar_doubles);
    array_show( sorted_array, num_of_elements );

    return sorted_array;
}
double DynamicArray_median ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double mid_value_1, mid_value_2, median;
    double *sorted_array = DynamicArray_copy_and_sort( da );
    int sort_array_size = DynamicArray_size( da );
    /*Determine if # of elements is even or odd; if odd, median is middle value,
    if even, median is average of two middle values*/
    if ( sort_array_size % 2 == 0 ) { 
        mid_value_1 = sorted_array[sort_array_size/2];
        mid_value_2 = sorted_array[(sort_array_size/2)-1];
        median = (mid_value_1+mid_value_2) / 2;
        free( sorted_array );   //Free up space taken up by sorted_array since we no longer need it
        return median;
    }
    else {
        median = sorted_array[sort_array_size/2];
        free( sorted_array );
        return median;
    }
}

double DynamicArray_sum ( const DynamicArray * da ) {
    double sum = 0;
    for ( int i = da->origin; i < da->end; i++) {
        sum = sum + da->buffer[i];
    }
    return sum;
}

/*EXERCISE 2************************************************/
double DynamicArray_last ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return da->buffer[ (da->end)-1 ];
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    return da->buffer[ da->origin ];
}

/*EXERCISE 3************************************************/
DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray * da_new = (DynamicArray *) malloc(sizeof(DynamicArray));
    da_new->capacity = da->capacity;
    da_new->origin = da->origin;
    da_new->end = da->end;
    da_new->buffer = (double *) calloc ( da->capacity, sizeof(double) );
    memcpy((da_new->buffer)+(da->origin), (da->buffer)+(da->origin), DynamicArray_size(da)*sizeof(double));
    DynamicArray_track( da_new );
    return da_new;
}

/*EXERCISE 4*************************************************/
DynamicArray * DynamicArray_range ( double a, double b, double step) {
    DynamicArray *da_r = DynamicArray_new();
    int end_element = (b-a)/step;
    for ( int i = 0; i <= end_element; i++ ) {
        DynamicArray_set(da_r, i, a);
        a = a + step;
    }
    return da_r;
}

/*EXERCISE 5************************************************/
DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    // DynamicArray *c = (DynamicArray *) malloc(sizeof(DynamicArray));
    // c->origin = a->origin;
    // c->end = a->end + DynamicArray_size(b);
    // c->capacity = (a->end) + ((b->capacity) - (b->origin));
    // c->buffer = (double *) calloc ( c->capacity, sizeof(double) );

    // memcpy((c->buffer)+(c->origin), (a->buffer)+(a->origin), DynamicArray_size(a)*sizeof(double));
    // memcpy((c->buffer)+(a->end), (b->buffer)+(b->origin), DynamicArray_size(b)*sizeof(double));
    // DynamicArray_track( c );
    // return c;
    DynamicArray *c = DynamicArray_copy(a);
    int size_c = DynamicArray_size(c);
    int size_b = DynamicArray_size(b);
    for (int i = size_c; i < size_b; i++ ) {
        for (int j = 0; j < size_b; j++) {
            DynamicArray_set( c, i, c->buffer[j]);
        }
    }
    return c;
}

/*EXERCISE 6***********************************************/
/*Function to take sub_array for the DynamicArray_take function*/   
DynamicArray * DynamicArray_take_subarray ( const DynamicArray * a, int n ) {
    int array_size = DynamicArray_size( a );
    if ( abs(n) > array_size ) { return DynamicArray_subarray( a, 0, array_size ); }
    if ( n >= 0 ) {
        return DynamicArray_subarray( a, 0, n );
    } 
    return DynamicArray_subarray( a, array_size + n, array_size);
}
/*Function to add zeros to rest of the array if requested n elements is greater than the array size*/   
void DynamicArray_push_zeros ( DynamicArray * a, int num_of_zeros, bool push_to_front) {
    for (int i = 0; i < num_of_zeros; i++ ) {
        if ( push_to_front ) {
            DynamicArray_push_front( a, 0.0 );
        } else {
            DynamicArray_push( a, 0.0 );
        }
    }
}

DynamicArray * DynamicArray_take ( const DynamicArray * a, int n ) {
    assert(a->buffer != NULL);
    int array_size = DynamicArray_size( a );
    int num_of_zeros = abs(n) - array_size;
    DynamicArray *sub_a = DynamicArray_take_subarray( a , n );
    if ( num_of_zeros > 0 ) {
        DynamicArray_push_zeros( sub_a, num_of_zeros, n > 0 );
    }
    DynamicArray_track( sub_a );
    return sub_a;
} 

/*EXERCISE 7************************************************************/
/*Function that points to the next array created*/
void DynamicArray_track ( DynamicArray * a ) {
    if ( first_array == NULL ) {    /*if only one array was inputted*/
        first_array = a;
        last_array = a;
        number_of_arrays_allocated++;
        return;
    }
    /*Point the DA->next array to the next array and move the last_array pointer to the last array*/
    last_array->next_array = a;
    last_array = a;
    number_of_arrays_allocated++;
}

int DynamicArray_num_arrays() {
    return number_of_arrays_allocated;
}

void DynamicArray_destroy(DynamicArray * da) {
    if ( da->buffer == NULL ) { return; }
    free(da->buffer);
    da->buffer = NULL;
    return;
}
int DynamicArray_destroy_all() {
    int count_destroyed = 0;
    if ( first_array == NULL ) { return 0; }
    for ( DynamicArray *current_element = first_array; 
        current_element != last_array; 
        current_element = current_element->next_array ) {
        DynamicArray_destroy( current_element );
        count_destroyed++;   
        number_of_arrays_allocated--;

    }
    DynamicArray_destroy( last_array );
    count_destroyed++;
    number_of_arrays_allocated--;
    return count_destroyed;
}

int DynamicArray_is_valid(const DynamicArray * da) {
    if ( da->buffer == NULL ) { return 0; }
    return 1;
    /*return da->buffer == NULL ? 0 : 1;*/
}



