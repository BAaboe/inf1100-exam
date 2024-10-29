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

  // preprocessing
  strip_newlines(buffer);
  strip_comments(buffer);

  char *token = buffer; 
  char *end;
  char terminator;

  // breaks the program text into meaningfulwords and places each word in the
  // global program array
  int i = 0;
  while (*token != '\0') {
    while (*token == ' ') token++;
    end = token;
    
    // if token starts with ~ it is a string and we must scan up to the 
    // closing ~, otherwise we're looking for a space
    if (*token == '~') {
      terminator = '~';
      end++;
    } else { 
      terminator = ' ';
    }

    // finds end of token
    while (*end != terminator && *end != '\0') end++;
    
    if (*end == '~') end++;

    // copy the token to its own string pointed to by the program array
    if (token < end) {
      int nchar  = end - token;
      program[i] = malloc(sizeof(char)*(nchar + 1));
      memcpy(program[i], token, sizeof(char)*nchar);
      program[i][nchar] = '\0';
      i++;
    }

    // need this not to skip past the end of string marker by accident; could
    // proably be solved more elegantly.
    if (*end != '\0') token = end + 1;
    else token = end;
  }

  free(buffer);

  return program;
}

