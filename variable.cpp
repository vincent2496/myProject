#include "variable.h"

Variable::Variable(string s):_symbol(s),_value(s){}
string Variable::value(){ return _value; }

string Variable::symbol() const{
	return _symbol;
}

bool Variable::getAssignable(){
	return _assignable;
}

bool Variable::setAssignable(){
	return true;
}

bool Variable::setNonAssignable(){
	return false;
}

bool Variable::setSymbol(string string){
	return false;
}

bool Variable::match(Term &term){}

bool Variable::match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
        _value = atom._symbol ;
        _assignable = false;
    }
	else{
        ret = (_value == atom.symbol());
    }
    return ret;
}

 bool Variable::match( Number number ){
    bool ret = _assignable;
    if(_assignable){
        _value = number.value() ;
        _assignable = false;
    }else{
         ret = (_value == number.value());
    }
    return ret;
}
