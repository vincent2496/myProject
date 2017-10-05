#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#include <iostream>
#include <string>
#include "atom.h"
#include "variable.h"

using namespace std;

class Atom;
class Variable;

class Number{
public:
    Number(int i);
    string symbol();
    string value();  
    bool match(Number number);
    bool match(Atom atom);
	bool match(Variable &variable);
private:
    int _value = 0;
	string _symbol = "";
} ;

#endif // NUMBER_H_INCLUDED
