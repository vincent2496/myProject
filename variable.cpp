#include "variable.h"

string Variable::value(){ return _value; }

bool getAssignable(){
	
}

bool setAssignable(){
	return true;
}

bool setNonAssignable(){
	return false;
}

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