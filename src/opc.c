#include "opc.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


//Pops from the stack and makes sure its a int
int getInt(stack_t* stack, int shrink){
	stackData_t stackData;
	if(shrink){
		stackData = pop(stack);
	}else{
		stackData = pop_without_shrinking(stack);
	}
	if(stackData.type){
		printf("\33[1;31mError:\33[0m Can't do numeric operations on strings\n");
		exit(-1);
	}
	return stackData.data.iData;
}

//Numeric operations
void add(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2+val1);

}
void sub(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2-val1);
}
void mult(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2*val1);
}
void divide(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2/val1);
}
void mod(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2%val1);
}
void eq(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2==val1);
}
void gr(stack_t* stack){
	int val1 = getInt(stack,1);
	int val2 = getInt(stack,0);
	pushi(stack, val2>val1);
}

//Stack operations
void dup(stack_t* stack){
	stackData_t stackData = pop(stack);

	push(stack, stackData);
	push(stack, stackData);
}

void swap(stack_t* stack){
	stackData_t stackData1 = pop_without_shrinking(stack);
	stackData_t stackData2 = pop_without_shrinking(stack);

	push(stack, stackData1);
	push(stack, stackData2);
}

//PC operations
int cjmp(stack_t* stack, int pc){
	stackData_t dpc = pop(stack);
	stackData_t conditonFlag = pop(stack);
	if(dpc.type || conditonFlag.type){
		printf("\33[1;31mError:\33[0m .cjump needs two integers at the top of the stack\n");
		exit(-1);
	}
	if(conditonFlag.data.iData){
		return pc+dpc.data.iData-1;
	}
	return pc;
}

//I/O operations
void print(stack_t* stack){
	stackData_t stackData = pop(stack);
	if(stackData.type){
		printf("%s", stackData.data.strData);
		free(stackData.data.strData);
	}else {
		printf("%d", stackData.data.iData);
	}
}

void newline(stack_t* stack){
	printf("\n");
}
