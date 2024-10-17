#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "stack.h"

typedef struct {
	int pc;
	stack_t* stack;
	char** program;
} interpreter_t;

//Creates an interpreter object
interpreter_t* createInterpreter(int stackSize, char** program);
//Frees an interpreter object
void freeInterpreter(interpreter_t* interpreter); 

//Interprets an instruction and calls the correct operation or pushes the right value
void interpret(interpreter_t* interpreter, char* instruction);

//Gets the next instruction
char* step(interpreter_t* interpreter);

#endif
