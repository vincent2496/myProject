#ifndef TERM_H
#define TERM_H
#include <string>

using namespace std;

class Term{

public:
    virtual string symbol() const= 0;
    virtual string value() const{
      return symbol();
    };
    virtual bool match(Term & term) {
      return symbol() == term.symbol();
    }
	virtual int arity(){
		return 0;
	};
};

#endif