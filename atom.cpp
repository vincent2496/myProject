#include "number.h"

using namespace std;

Atom::Atom (string s):_symbol(s) {}

string Atom::symbol() const{
    return _symbol;
}

bool Atom::match(Term &term){
	Variable *variable = dynamic_cast<Variable*>(&term);
/*
    if (variable->_assignable){
	  variable->match(*this);
	  variable->_assignable = false;
	  return true;
    }
    else
        return _symbol == variable->value();
*/
}

/*
bool Atom::match(Variable &variable){
    if(variable._assignable){    
        variable.match(*this);	
        variable._assignable = false;
	    return true;
    }
	else
        return _symbol == variable.value();
}
*/