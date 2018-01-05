#ifndef EXP_H
#define EXP_H
#include <string>
#include "atom.h"
#include <iostream>
#include "variable.h"

class Exp {
public:
  virtual string value() = 0;
  virtual bool evaluate() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right), match(true), result(true){

  }

  bool evaluate(){
    //return _left->match(*_right);

  if((_left->getVariable()&&_left->getVariable()->symbol() == _left->getVariable()->value()) ||
     (_right->getVariable()&&_right->getVariable()->symbol() == _right->getVariable()->value()))
      match = true;
  else 
      match = false; 
      result = _left->match(*_right);
  return result;
  }
public:
  string value(){
    if(result){
        if((_left->getVariable() && _right->getVariable() && _left->getVariable()->value() == _right->getVariable()->value()) || !match)
            return "true";
        else 
            return _left->symbol() + " = " + _right->value();
    }
    else return "false";
  }
private:
    bool result;
	bool match;
private:
    Term* _left;
    Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }
  string value(){
      if(result){
          if(_right->value()=="true")
              return _left->value();
          else if(_left->value()=="true")
              return _right->value();
          else  
              return _left->value() + ", " + _right->value();
      }
      else return "false";
  }

  bool evaluate() {
      result = (_left->evaluate() && _right->evaluate());
      return result;
  }

private:
  bool result;
private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

  bool evaluate() 
  {
    //return (_left->evaluate() || _right->evaluate());
    lResult = _left->evaluate();
    rResult = _right->evaluate();
    result = (lResult||rResult);
    return result;
  }

  string value(){
    if(lResult && (!rResult || _right->value()=="true")) 
        return _left->value();
    else if(!lResult && (rResult || _right->value()=="true")) 
        return _right->value();
    return _left->value() + "; " + _right->value();
  }  

private:
  bool result;

  bool rResult;
  bool lResult;
private:
  Exp * _left;
  Exp * _right;
};
#endif
