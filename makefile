INC_DIR = include

all: hw8 shell

hw8: main.o atom.o struct.o list.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw8 main.o atom.o struct.o list.o -lgtest
else
	g++ -o hw8 main.o atom.o struct.o list.o -lgtest -lpthread
endif
shell: shell.o list.o struct.o atom.o

ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o atom.o struct.o list.o -lgtest
else
	g++ -o shell shell.o atom.o struct.o list.o -lgtest -lpthread
endif

main.o: main.cpp expression.h exception.h utExp.h exp.h
#parser.h global.h scanner.h
	g++ -std=gnu++0x -c main.cpp
#number.o: number.h atom.h variable.h number.cpp
#	g++ -std=gnu++0x -c number.cpp
#variable.o: variable.h atom.h number.h variable.cpp
#	g++ -std=gnu++0x -c variable.cpp
atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
struct.o: atom.h struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp
list.o: atom.h struct.cpp list.h
	g++ -std=gnu++0x -c list.cpp
#term.o: variable.h iterator.h term.h
#	g++ -std=gnu++0x -c term.cpp
shell.o: parser.h shell.cpp scanner.h
	g++ -std=gnu++0x -c shell.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o exp
endif
stat:
	wc *.h *.cpp