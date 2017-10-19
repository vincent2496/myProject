#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "atom.h"
#include "number.h"
#include "term.h"


using namespace::std;

class Atom;
class Number;

class Variable : public Term{
public:
    Variable(string s);//:_symbol(s){}
    string const _symbol;

	string symbol() const;
    string value() const;
	bool match(Term &term);
    //bool match(Atom atom);
    //bool match(Number num);

	bool getAssignable();
	bool setAssignable(bool assignable);
	void setNonAssignable();
	bool setSymbol(string string);
  void setValue(string str);
	void setVariableValue(string s);
	void setVariable(Variable *variable);
	friend class Atom;
	friend class Number;
private:
    string _value;
    bool _assignable = true;
	  vector<Variable *> _variable;

	bool _isStruct = false;
    static string temp;
};

#endif
