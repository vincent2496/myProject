#ifndef NUMBER_H
#define NUMBER_H

#include "atom.h"
#include "variable.h"
#include "term.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Atom;
class Variable;

class Number : public Term{
public:
    Number(double i);
    string symbol() const;
	bool match(Term &term);
private:
	string _symbol;
	string _value;
} ;

#endif 
