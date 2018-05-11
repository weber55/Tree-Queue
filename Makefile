all: TreeDr

TreeDr: TreeDr.o TreeType.o QueType.o
	g++ TreeDr.o TreeType.o QueType.o -o TreeDr

TreeDr.o: TreeDr.cpp TreeType.h
	g++ -c -Wall -std=c++14 -g -O0 -pedantic-errors TreeDr.cpp

TreeType.o: TreeType.cpp TreeType.h
	g++ -c -Wall -std=c++14 -g -O0 -pedantic-errors TreeType.cpp

QueType.o: QueType.cpp QueType.h
	g++ -c -Wall -std=c++14 -g -O0 -pedantic-errors QueType.cpp

clean:
	rm -f TreeDr
	rm -f TreeDr.o
	rm -f TreeType.o
	rm -f QueType.o
