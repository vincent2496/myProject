#include "number.h"
#include <iostream>
using namespace std;

Atom::Atom (string s):_symbol(s) {}

string Atom::symbol() const{
    return _symbol;
}

/*bool Atom::match(Term &term){
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
}*/
  bool Atom::match(Term &term){
    cout << "11111111" << endl;
    bool ret = false;
    Variable *pt = dynamic_cast<Variable*>(&term);
    if(pt){
      if(pt->getAssignable()){
        pt->setNonAssignable();
  			ret = true;
  			pt->match(*this);
      }else{
        ret = (_symbol == term.symbol());
      }
    }else{
      ret = (_symbol == term.symbol());
    }
    return ret;
  }

//	  variable->match(*this);
//	  variable->_assignable = false;
//	  return true;
//    }
//    else
//        return _symbol == variable->value();

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

string symbol() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i<_args.size()-1; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]->symbol() + ")";
    return  ret;
  }
  bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size() != ps->_args.size())
        return false;
      for(int i=0; i<_args.size(); i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
  }

*/
