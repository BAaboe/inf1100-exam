#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer_preprocessor.h"
#include "interpreter.h"

char **program;

int main(int argc, char **argv) {
	if (argc < 2) {
	printf("no program supplied\n");
	return 0;
	}

	// program is an array of strings; the end of the program is signified by a
	// NULL pointer.
	program = load_program(argv[1]);

	//Creates a interpreter object, with a stack with starting size of 5, and loads the program.
	interpreter_t* interpreter = createInterpreter(5, program);
	//Steps through every word in the program
	while(1){
		//Gets current instruction
		char* instruction = step(interpreter);
		//Check if at the end of program
		if(instruction == NULL){break;}
		//Interpret the instruction
		interpret(interpreter, instruction);
	}

	free(interpreter);

	//test();
	// prints out the words in the program array; uncomment to get an idea of how
	// the program is stored in memory.
	// for (char **pc = program; *pc != NULL; pc++) {
	// 	printf("program[%i]: %s\n", (int) (pc - program), *pc);
	// }

	return 0;
}
