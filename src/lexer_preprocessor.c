#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lexer_preprocessor.h"

char *read_file(char *source_file) {
  char *buffer;
  size_t len;
  FILE *f = fopen(source_file, "rb");

  // find length of file
  fseek(f, 0, SEEK_END);
  len = ftell (f);
  fseek(f, 0, SEEK_SET);

  // allocate space, read file
  buffer = malloc(len+1);
  fread(buffer, sizeof(char), len, f);
  fclose(f);

  // no terminating zero in your typical file; need to add it
  buffer[len] = '\0';

  return buffer;
}

// replace all newlines with a space
void strip_newlines(char *str) {
  for (char *pt = str; *pt != '\0'; pt++) {
    if (*pt == '\n') *pt = ' ';
  }
}

// replace all (comments) with spaces
void strip_comments(char *str) {
	int par_count = 0;
	char is_string = 0;
  for (char *pt = str; *pt != '\0'; pt++) {
		if(*pt == '~'){
			is_string^=0b1;
		}
		if(!is_string){
			if (*pt == '(') {
				par_count++;
			} else if(*pt == ')'){
				par_count--;
				*pt = ' ';
			}
		}
		if(par_count != 0){
			*pt = ' ';
		}
	}
}

char** load_program(char *src_file) {
  // allocate space for the program to live in
  char **program = calloc(MAXWORDS, sizeof(char*));

  char *buffer = read_file(src_file);

	label_t* labeles;
	int labelec = 0;

  // preprocessing
  strip_newlines(buffer);
  strip_comments(buffer);
	
	//Need better system for this, maybe a Enum
	char reading = 0;
	char reading_str = 0;
	char reading_label = 0;

	int start;
	int i = 0;
	int token_count = 0;
	
  while(buffer[i] != '\0'){
		if(!reading && buffer[i] != ' '){
			reading = 1;
			start = i;
			if(buffer[i] == '~') reading_str=1;
			if(buffer[i] == '#') reading_label=1;

			i++;
			continue;
		}

		if(reading && ((buffer[i] == ' ' && !reading_str) || (buffer[i] == '~' && reading_str))){
			//Gets the positon of last character
			int end;
			if(reading_str){
				end = i+1;
			}else{
				end = i;
			}
			
			//Finds and stores where the label are located
			if(reading_label){
				labelec++;

				//Make new label
				label_t label;
				label.pos = token_count+1;
				label.label_name = calloc(end-start, sizeof(char));
				memcpy(label.label_name, buffer+start+1, end-start-1);
				label.label_name[end-start+1] = '\0';
				
				//Allocates more space for the labels
				if(labelec == 1){
					labeles = malloc(sizeof(label_t));
				} else{
					labeles = realloc(labeles, labelec*sizeof(label_t));
				}
				
				//Stores the label
				labeles[labelec-1] = label;

				reading = 0;
				reading_label = 0;
				continue;
			}

			//Allocates space for the token
			char* token = calloc(end-start+1, sizeof(char));

			//Copies the right token to the newly allocated space
			memcpy(token, buffer+start, end-start);
			//Makes sure that the string is zero terminated
			token[end-start+1] = '\0';

			//Check if macro
			if(!strcmp(token, ".cgoto")){
				char found = 0;
				//Finds the label in the label list
				for(int j = 0; j<labelec; j++){
					if(!strcmp(labeles[j].label_name, program[token_count-1])){
						//Calculates how many steps back you need to go
						int steps = token_count-labeles[j].pos;
						
						//Gets how many digits ther is
						int n = steps;
						int count = 0;
						do{
							n/=10;
							count++;
						}while(n != 0);
						count++;

						//Creates the tokens for number of steps
						char* newToken = calloc(++count, sizeof(char));
						sprintf(newToken, "%d",-steps);

						//Replaces the token .goto with the token .cjump
						token = realloc(token, sizeof(".cjump"));
						token = ".cjump";

						//Adds the token to the program
						program[token_count-1] = newToken;
						program[token_count] = token;

						found = 1;
						break;
						

					}
				}
				if(!found){
					printf("\33[1;31mError:\33[0m Lable not found\n");
				}
			}else{
				//Adds the token to to the program
				program[token_count] = token;
			}

			token_count++;

			reading = 0;
			reading_str = 0;
			reading_label = 0;
		}

		i++;
  }

  free(buffer);

  return program;
}

