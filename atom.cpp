#include "number.h"

using namespace std;

//Atom::Atom (string s):_symbol(s) {}

string Atom::symbol() const{
    return _symbol;
}

bool Atom::match(Term &term){
	Variable *variable = dynamic_cast<Variable*>(&term);
    if (variable){
		bool ret = variable->getAssignable();
		if(variable->getAssignable() == true ){
			variable->setNonAssignable();
			ret = true;
			variable->setSymbol(_symbol);
		}
		else{ret =false;}
	}
	else{return term.symbol() == symbol();}
}
