#ifndef ATOM_H
#define ATOM_H

#include "variable.h"
#include "number.h"
#include "term.h"

#include <string>

using std::string;
using namespace::std;

class Variable;
class Number;

class Atom : public Term{
public:
    //Atom(string s);
    Atom(string s):Term(s) {}
	//string symbol() const;
	bool match(Term &term);
    friend class Variable;
//private:
    string _symbol;
};

#endif
