#include "number.h"

using namespace std;

string numberToString(double d){
	std::stringstream ss;
	string ret;
	ss << d;
	ss >> ret;
	return ret;
}

//Number::Number(double d):_symbol(numberToString(d)),_value(numberToString(d)){}
/*
string Number::symbol() const{
    return _symbol;
}

bool Number::match(Term &term){
    Variable *var = dynamic_cast<Variable *>(&term);
    if(var){
        bool ret = var->getAssignable();
        if(var->getAssignable()==true || var->value() == _value){
            var->setVariableValue(_value);
            ret = true;
        }else{ret = false;}
        return ret;}
}
*/