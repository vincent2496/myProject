#include "term.h"
#include "variable.h"
#include "iterator.h"
#include <typeinfo>
#include "list.h"

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  else
    return symbol() == a.symbol();
}

Iterator<Term *> * Term::createIterator(){
  return new NullIterator<Term *>(this);
}