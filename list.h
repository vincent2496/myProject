#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"
#include <vector>
#include <string>

using std::vector;
using namespace std;

class List : public Term{
public:
    List(): _elements(){}
    List (vector<Term *> const & elements):_elements(elements){}
    string symbol() const;
    string value() const;
    bool match(Term & term);

    Term * head() const;
    List * tail() const;
	Term * element(int i);
    int length() const;
    vector<Term *> elements();
private:
    vector<Term *> _elements;
};

#endif