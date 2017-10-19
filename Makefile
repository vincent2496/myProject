INC_DIR = include

all: hw3

hw3: main.o number.o variable.o atom.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o number.o variable.o atom.o struct.o -lgtest
else
	g++ -o hw3 main.o number.o variable.o atom.o struct.o -lgtest -lpthread
endif
#utTerm.h
main.o: main.cpp utStruct.h utVariable.h  
	g++ -std=gnu++0x -c main.cpp
number.o: number.h atom.h variable.h number.cpp
	g++ -std=gnu++0x -c number.cpp
variable.o: variable.h atom.h number.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
atom.o: variable.h atom.h number.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
struct.o: variable.h atom.h number.h struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
