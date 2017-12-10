#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"

template <class T> 
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T> 
class NullIterator : public Iterator<T> {
public:
  NullIterator(Term *n){}
  //NullIterator(){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
};

template <class T> 
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template <class T> 
class ListIterator :public Iterator<T> {
public:
  ListIterator(List *list): _index(0), _list(list) {}
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
  int _index;
  List* _list;
};

template <class T>
class DFSIterator : public Iterator<T>{
public:
  DFSIterator(vector <Term*> DFSvec ) : _index(0), _DFSVec(DFSvec) {}
  
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _DFSVec[_index];
  }

  bool isDone() const {
    return _index >= _DFSVec.size();//_list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  vector<Term *> _DFSVec;
};

template <class T>
class BFSIterator : public Iterator<T> {
public:
  BFSIterator(vector <Term*> BFSvec ) : _index(0), _BFSVec(BFSvec) {}
  
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _BFSVec[_index];
  }

  bool isDone() const {
    return _index >= _BFSVec.size();//_list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  vector<Term *> _BFSVec;
};

#endif
