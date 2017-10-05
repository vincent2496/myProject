#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "variable.h"
#include "number.h"

using std::string;

class Variable;
class Number;

class Atom {
public:
    Atom (string s):_symbol(s) {}
    bool operator ==(Atom a) {return _symbol == a._symbol;}
    string symbol();
    bool match(Number number);
	bool match(Variable &variable);
    friend class Variable;
	friend class Number;
private:
    string _symbol;
};

#endif
