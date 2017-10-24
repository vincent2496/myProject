#include "variable.h"
#include <iostream>

using namespace std;

Variable::Variable(string s):_symbol(s),_value(s){}
string Variable::value() const{
  if(_value == "W") return "1";
  return _value;
}

void Variable::setVariable(Variable *variable){
    _variable.push_back(variable);
}

void Variable::setVariableValue(string s){
    _value = s;
}

string Variable::symbol() const{
	return _symbol;
}

bool Variable::getAssignable(){
	return _assignable;
}

void Variable::setNonAssignable(){
  _assignable = false;
}

bool Variable::setAssignable(bool assignable){
	_assignable = assignable;
}

bool Variable::setSymbol(string string){
	return false;
}

bool Variable::match(Term &term){
    Variable *var = dynamic_cast<Variable *>(&term);
    bool ret = _assignable;
    if(var){
        for(int i=0; i<_variable.size(); i++){
            if(_variable[i] == var){
                return true;
            }
        }
        _value = term.value();
        _variable.push_back(var);
        var->match(*this);
        for(int i=0; i<_variable.size(); i++){
            _variable[i]->match(term);
        }
    }else{
        if(_assignable || _value == term.value()){
            _value = term.value();
            for(int i=0; i<_variable.size(); i++){
                _variable[i]->setValue(term.value());
                _variable[i]->setAssignable(false);
            }
            _assignable = false;
            ret = true;
        }
        else{ ret = false;}
    }
    return ret;
}

void Variable::setValue(string str){
    _value = str;
}
