#ifndef VARIABLE_H
#define VARIABLE_H
#include "atom.h"
#include "number.h"
#include "term.h"
#include "list.h"
#include <string>
#include <vector>

using namespace::std;

class Atom;
class Number;

class Variable : public Term{
public:
    Variable(string s);	
    string const _symbol;
	//string symbol() const;
    string value() const;	
	bool match(Term &term);
	bool getAssignable();
	bool setAssignable(bool assignable);
	bool setSymbol(string string);		
	void setNonAssignable();
    void setValue(string str);
	void setVariableValue(string s);
	void setVariable(Variable *variable);
	friend class Atom;
	friend class Number;
private:
    string _value;
	vector<Variable *> _variable;	
    bool _assignable = true;
	bool _isStruct = false;
    static string temp;
	Term *t;
};

#endif
