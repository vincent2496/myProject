#ifndef STRUCT_H
#define STRUCT_H
#include "atom.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Number;
class variable;

class Struct : public Term
{
public:
    Struct(Atom const & name, std::vector<Term *> args);
    Term * args(int index);
    Atom const & name();
    string symbol() const;
    string value() const;
    bool match(Term &term);
private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
