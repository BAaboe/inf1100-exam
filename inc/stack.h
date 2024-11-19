#ifndef STACK_H
#define STACK_H

//Builds downwards, because its easier

//Union for the data in the stack, since it can be both int or str
typedef union {
	int iData;
	char* strData;
} data_t;

//Struct of the stack element
typedef struct{
	int type; //1 for str, 0 for int
	data_t data;
} stackData_t;

//Struct to contain all the stack elements, size of stack, and stack pointer
typedef struct {
	stackData_t* stack;
	int size;
	int minSize;
	int sp;
} stack_t;


//Pops the top element from the stack and returns it
stackData_t pop(stack_t* stack);
stackData_t pop_without_shrinking(stack_t* stack);

//Push a stackData_t to the stack
void push(stack_t* stack, stackData_t data);
//Makes a stackData_t from a string and pushes it to the stack
void pushi(stack_t* stack, int value);
//Makes a stackData_t from a integer and pushes it to the stack
void pushstr(stack_t* stack, char* str);

//Returns a newly created stack, with a startSize
stack_t* createStack(int startSize);

//Frees the stack from memory
void freeStack(stack_t* stack);

#endif
