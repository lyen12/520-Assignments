#ifndef RPN_H
#define RPN_H

#include <stdlib.h>

typedef enum {
    OK, 
    NOT_INITIALIZED_ERROR, 
    POP_ERROR, 
    UNARY_ERROR, 
    BINARY_ERROR, 
    OVERFLOW_ERROR,
    DIVIDE_BY_ZERO_ERROR
} RPN_ERROR;

void rpn_show();

/*rpn_init function creates a new array to implement the stack. 
It also sets an index to the top of the stack to zero. If the 
init method has been called already, then it frees the old stack 
and creates a new stack. It should also clear errors.*/
void rpn_init();

/*rpn_push function pushes its argument onto the stack.*/
void rpn_push(double x);

/*rpn_add function pops the top two values off the top of the stack 
and pushes their product onto the stack.*/
void rpn_add();

/*rpn_negate function negates the value on the top of the stack.*/
void rpn_negate();

/*rpn_multiply function pops the top two values off of the stack 
and pushes their product onto the stack.*/
void rpn_multiply();

/*rpn_div function divides the second to the top element of the stack 
with the top element of the stack.*/
void rpn_div();			//Exercise

/*rpn_pop function pops the top value off the stack and returns it.*/
double rpn_pop();

RPN_ERROR rpn_error();

/*rpn_free function should free the memory used by the rpn, and un-initialized it*/
void rpn_free();

#endif