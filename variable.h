#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"

using namespace::std;

class Atom;
class Number;

class Variable{
public:
    Variable(string s):_symbol(s){}
    string const _symbol;
    string value();
    bool match( Atom atom );
    bool match( Number num );
    friend class Atom;
	friend class Number;
private:
    string _value;
    bool _assignable = true;
};

#endif
