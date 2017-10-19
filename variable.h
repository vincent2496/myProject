#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
#include "term.h"
//#include "struct.h"

using namespace::std;

class Atom;
class Number;

class Variable : public Term{
public:
  Variable(string s);//:_symbol(s){}
  string const _symbol;

	string symbol() const;
  string value() const{
    if(_value == "W") return "1";
    return _value;
  }
	bool match(Term &term);
  bool match(Atom atom);
  bool match(Number num);

	bool getAssignable();
	bool setAssignable();
	bool setNonAssignable();
	bool setSymbol(string string);

  friend class Atom;
	friend class Number;
  private:
    string _value;
	//string _symbol;
    bool _assignable = true;

};

#endif
