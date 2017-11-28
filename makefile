INC_DIR = include

all: hw6

hw6: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 main.o -lgtest
else
	g++ -o hw6 main.o -lgtest -lpthread
endif
	
main.o: main.cpp utParser.h term.h atom.h number.h variable.h struct.h list.h node.h
	g++ -std=gnu++0x -c main.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw6
endif