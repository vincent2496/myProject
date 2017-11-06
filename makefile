INC_DIR = include

all: hw5

hw5: main.o number.o variable.o atom.o struct.o list.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o number.o variable.o atom.o struct.o list.o -lgtest
else
	g++ -o hw5 main.o number.o variable.o atom.o struct.o list.o -lgtest -lpthread
endif

main.o: main.cpp
	g++ -std=gnu++0x -c main.cpp
number.o: number.h atom.h variable.h number.cpp
	g++ -std=gnu++0x -c number.cpp
variable.o: variable.h atom.h number.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
atom.o: variable.h atom.h number.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
struct.o: variable.h atom.h number.h struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp
list.o: variable.h atom.h number.h struct.cpp list.h
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif