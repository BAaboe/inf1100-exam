#ifndef __LEXER_PREPROCESSOR_H__
#define __LEXER_PREPROCESSOR_H__

// no program can be more than MAXWORDS long
#define MAXWORDS 1024

// loads an .8f program
char** load_program(char *src_file);

// creates a character array and reads a text file into it
char *read_file(char *source_file);

// replace all newlines with a space
void strip_newlines(char *str);

// replace all (comments) with spaces
void strip_comments(char *str);

#endif
