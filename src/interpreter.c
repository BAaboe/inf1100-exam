#include "interpreter.h"
#include "opc.h"
#include "stack.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//interprets the instruction and calls the rigth operation or pushes the right value to the stack
void interpret(interpreter_t *interpreter, char *instruction){
	//Operations
	if(instruction[0] == '.'){
		//Numeric operations
		if(!strcmp(&instruction[1], "+")){
			add(interpreter->stack);
		} else if (!strcmp(&instruction[1], "-")) {
			sub(interpreter->stack);
		} else if (!strcmp(&instruction[1], "*")) {
			mult(interpreter->stack);
		} else if (!strcmp(&instruction[1], "/")) {
			divide(interpreter->stack);
		} else if (!strcmp(&instruction[1], "mod")) {
			mod(interpreter->stack);
		} else if (!strcmp(&instruction[1], "=?")) {
			eq(interpreter->stack);
		} else if (!strcmp(&instruction[1], ">?")) {
			gr(interpreter->stack);
		}		

		//Stack operations
		else if(!strcmp(&instruction[1], "dup")){
			dup(interpreter->stack);
		}
		else if(!strcmp(&instruction[1], "swap")){
			swap(interpreter->stack);
		}

		//PC operations
		else if(!strcmp(&instruction[1], "cjump")){
			interpreter->pc = cjmp(interpreter->stack, interpreter->pc);
		}

		//I/O operations
		else if(!strcmp(&instruction[1], "print")){
			print(interpreter->stack);
		} else if(!strcmp(&instruction[1], "newline")){
			newline(interpreter->stack);
		}else{
			printf("\33[1;31mError:\33[0m Instruction \"%s\" does not exists\n", &instruction[1]);
			exit(-1);
		}
	}
	//String push
	else if(instruction[0] == '~'){
		int len = strlen(&instruction[0])-1;//Minus one to remove back tilde
		//Allocates space for the str
		char* str = malloc(sizeof(char)*len);
		//Copy everything except the tildes to the newly allocated string
		strcpy(str, &instruction[1]);
		//Makes sure the string is zero terminated
		str[len-1] = '\0';
		//Pushes the string to the stack
		pushstr(interpreter->stack, str);
	}
	//Integer push
	else{
		int len = 0;

		//Checks if the string only contains integers
		int isInt = 1;
		while(*instruction){
			if (isdigit(*instruction) == 0 && *instruction != '-') {
				isInt = 0;
				break;
			}
			instruction++;
			len++;
		}
		instruction-=len;

		//Gives an error if the string contains anything other the an integer
		if(!isInt){
			printf("\33[1;31mError:\33[0m Can't push non integer as integer\n");
			exit(-1);
		}

		//Pushes the number to the stack
		pushi(interpreter->stack, atoi(instruction));
	}
}

//Gets the current instruction
char* step(interpreter_t* interpreter){
	char* instruction = interpreter->program[interpreter->pc];
	interpreter->pc++;
	return instruction;
}

//Creates a interpreter object
interpreter_t* createInterpreter(int stackSize, char** program){
	//Creates an stack
	stack_t* stack = createStack(stackSize);
	interpreter_t* interpreter = malloc(sizeof(interpreter_t));
	
	//Initialize values
	interpreter->stack=stack;
	interpreter->pc=0;
	interpreter->program = program;

	return interpreter;
}

//Frees the interpreter object
void freeInterpreter(interpreter_t *interpreter){
	freeStack(interpreter->stack);
	free(interpreter);
}
