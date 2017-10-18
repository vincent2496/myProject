#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>
#include "atom.h"
#include "variable.h"
//#include "term.h"

using namespace std;

class Atom;
class Variable;

class Number{// : public Term{
public:
    Number(double i);
    string symbol();
    string value();  
    bool match(Number number);
    bool match(Atom atom);
	bool match(Variable &variable);
private:
    double _value = 0;
	string _symbol = "";
} ;

#endif 
