#include "number.h"

//Atom::match(){
	
//}

string Atom::symbol(){
  return  _symbol;
}

bool Atom::match(Number number){
    return _symbol == number.symbol();
}

bool Atom::match(Variable &variable){
    if(variable._assignable){    
        variable.match(*this);	
        variable._assignable = false;
	    return true;
    }
	else
        return _symbol == variable.value();
}
