#ifndef ITERATOR_H
#define ITERATOR_H

#include "term.h"
#include "struct.h"
#include "list.h"

template <class T> 
class Iterator {
public:
  Iterator(Term * n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
};

template <>
class Iterator<Struct *> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

    void next() {
    _index++;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }
private:
  Iterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template <>
class Iterator<List *> {
public:
  friend class List;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
   Iterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

/*
class NullIterator : public Iterator<class T>{
public:
  NullIterator(Term *n);
  void first();
  void next();
  Term * currentItem() const;
  bool isDone() const;
};


class DFSIterator : public Iterator {
public:
  void first() {
    _index = 0;
  }
  void next() {
    _index++;
  }
  Term * currentItem() const {
      return _t;
  }
  bool isDone() const {
    return true;
  }
private:
  DFSIterator(T *t): _index(0), _t(t) {}
  int _index;
  T* _t;
};
 
class BFSIterator : public Iterator {
 
};
*/

#endif
