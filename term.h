#ifndef TERM_H
#define TERM_H
#include <string>

#include <string>
#include <sstream>
using std::string;

using namespace std;

class Term{

public:
    //virtual string symbol() const= 0;
    virtual string symbol() const 
	{
		return _symbol;
	}
	virtual string value() const{
      return symbol();
    }
    virtual bool match(Term & term) {
      return symbol() == term.symbol();
    }
	virtual int arity(){
		return 0;
	}
protected:
    Term ():_symbol(""){}
	string _symbol;
	Term (string s):_symbol(s) {}
	Term(double db){
        std::ostringstream strs;
        strs << db;
    _symbol = strs.str();
  }
};

#endif