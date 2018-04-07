# A simple makefile for CSE 100 P1

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
FLAGS= -g -Wall -std=c++11

BSTOBJ=  BSTInt.o BSTNodeInt.o

BSTHPP= BST.hpp BSTNode.hpp BSTIterator.hpp

all: bst main

bst: testBST.o $(BSTOBJ) $(BSTHPP)
	$(CC) $(FLAGS) -o bst testBST.o $(BSTOBJ)

main: main.o $(BSTHPP)
	$(CC) $(FLAGS) -o main main.o 

main.o: $(BSTHPP)
	$(CC) $(FLAGS) -c main.cpp

testBST.o: testBST.cpp BSTInt.h
	$(CC) $(FLAGS) -c testBST.cpp

BSTInt.o: BSTInt.cpp BSTInt.h BSTNodeInt.h
	$(CC) $(FLAGS) -c BSTInt.cpp

BSTNodeInt.o: BSTNodeInt.cpp BSTNodeInt.h
	$(CC) $(FLAGS) -c BSTNodeInt.cpp

clean:
	$(RM) main bst *.o
