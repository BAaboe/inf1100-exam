#ifndef OPC_H
#define OPC_H
#include "stack.h"

//All the operations, name explains them
void add(stack_t* stack);
void sub(stack_t* stack);
void mult(stack_t* stack);
void divide(stack_t* stack);
void mod(stack_t* stack);
void eq(stack_t* stack);
void gr(stack_t* stack);
void dup(stack_t* stack);
void swap(stack_t* stack);
int cjmp(stack_t* stack, int pc);
void print(stack_t* stack);
void newline(stack_t* stack);


#endif
