
CC=cc
FLAGS=-Wall -O2

all: tree

tree: tree.c tree.h
	$(CC) $(FLAGS) tree.c -o tree 

test: tree input_crashing.txt 
	./tree < input_crashing.txt

clean:
	rm -f tree 
