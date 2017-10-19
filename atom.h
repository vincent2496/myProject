#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "variable.h"
#include "number.h"
#include "term.h"

using std::string;
using namespace::std;

class Variable;
class Number;

class Atom : public Term{
public:
    Atom(string s);
	//~Atom();
    //Atom (string s):_symbol(s) {}
    //bool operator ==(Atom a) {return _symbol == a._symbol;}
    //string symbol();
    string symbol() const;
	//bool match(Number number);
	//bool match(Variable &variable);
	//bool match(Atom &atom);
	bool match(Term &term);
    friend class Variable;
private:
    string _symbol;
};

#endif
