CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

all: cTreeTest tTreeTest

cTreeTest: CTreeTest.o CTree.o
	$(CC) CTreeTest.o CTree.o -o cTreeTest

tTreeTest: TTreeTest.o 
	$(CC) TTreeTest.o -o tTreeTest

CTreeTest.o: CTreeTest.cpp CTree.h
	$(CC) $(CFLAGS) -c CTreeTest.cpp

CTree.o: CTree.cpp CTree.h
	$(CC) $(CFLAGS) -c CTree.cpp

TTreeTest.o: TTreeTest.cpp Tree.h
	$(CC) $(CFLAGS) -c TTreeTest.cpp

clean:
	rm -f *.o cTreeTest tTreeTest
