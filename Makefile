INC_DIR = include

all: hw2

hw2: main.o number.o variable.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o number.o variable.o atom.o -lgtest
else
	g++ -o hw2 main.o number.o variable.o atom.o -lgtest -lpthread
endif

main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp
number.o: number.h atom.h variable.h number.cpp
	g++ -std=gnu++0x -c number.cpp
variable.o: variable.h atom.h number.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
atom.o: variable.h atom.h number.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
