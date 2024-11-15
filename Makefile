# add your source files here:
SRC := $(wildcard src/*.c)

# add your header files here
INC := inc/lexer_preprocessor.h 
FLAGS := -g

8inf: 8inf.c $(SRC) $(INC)
	gcc $(FLAGS) -Iinc 8inf.c $(SRC) -o 8inf

run: 8inf
	./8inf

clean:
	rm 8inf

.PHONY: clean
