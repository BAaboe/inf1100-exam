#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

//Pops the top element from the stack and returns it
stackData_t pop(stack_t* stack){
	//Makes sure that there is something to pop
	if(stack->sp == 0){
		printf("\33[1;31mError:\33[0m Poping from empty stack\n");
		exit(-1);
	}
	stack->sp--;

	//Makes sure the stack shrinks when to big
	if(stack->size/(stack->sp+1) >= 2){
		if(stack->size/2 >= stack->minSize){
			stack->size = stack->size>>1;
			stack->stack = realloc(stack->stack, sizeof(stackData_t)*stack->size);
		}
	}

	return stack->stack[stack->sp];
}

stackData_t pop_without_shrinking(stack_t* stack){
	if(stack->sp == 0){
		printf("\33[1;31mError:\33[0m Poping from empty stack\n");
		exit(-1);
	}
	stack->sp--;

	return stack->stack[stack->sp];
}

//Push a stackData_t to the stack
void push(stack_t* stack, stackData_t data){
	// Make stack bigger when about to stack overflow
	if(stack->sp+1 == stack->size){
		stack->size = stack->size<<1;
		stack->stack = realloc(stack->stack, sizeof(stackData_t)*stack->size);
	}

	stack->stack[stack->sp] = data;
	stack->sp++;
}
//Push an int to the stack
void pushi(stack_t* stack, int value){
	stackData_t stackData;
	stackData.type = 0;
	stackData.data.iData = value;
	push(stack, stackData);
}
//Push a str to the stack
void pushstr(stack_t* stack, char* str){
	stackData_t stackData;
	stackData.type = 1;
	stackData.data.strData = str;
	push(stack, stackData);
}

//Returns a newly created stack, with a startSize
stack_t* createStack(int startSize){
	stack_t *stack = malloc(sizeof(stack_t));
	
	//Initialize values
	stack->minSize = startSize;
	stack->size = startSize;
	stack->sp = 0;
	stack->stack = malloc(sizeof(stackData_t)*stack->size);

	return stack;
}

//Frees the stack from memory
void freeStack(stack_t *stack){
	free(stack->stack);
	free(stack);
}
