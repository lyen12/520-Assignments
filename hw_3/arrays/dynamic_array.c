#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
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
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

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
    const double * one_double = (const double *)one;
    const double * two_double = (const double *)two;
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
    double *sorted_array = DynamicArray_copy_and_sort( da );
    int sort_array_size = DynamicArray_size( da );
    /*Determine if # of elements is even or odd; if odd, median is middle value,
    if even, median is average of two middle values*/
    if ( sort_array_size % 2 == 0 ) { 
        double mid_value_1 = sorted_array[sort_array_size/2];
        double mid_value_2 = sorted_array[(sort_array_size/2)-1];
        return (mid_value_1 + mid_value_2) / 2 ;
    }
    else {
        return sorted_array[sort_array_size/2];
    }

}
double DynamicArray_sum ( const DynamicArray * da ) {
    double sum = 0;
    for ( int i = da->origin; i < da->end; i++) {
        sum = sum + da->buffer[i];
    }
    return sum;
}

