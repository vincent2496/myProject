#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "number.h"
#include "variable.h"
#include <iostream>
#include <vector>
using namespace std;

class List : public Term
{
public:
  string symbol() const
  {
    string ret = +"[";
    if (!_elements.empty())
    {
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end() - 1; ++it)
        ret += (*it)->symbol() + ", ";
      ret += (*it)->symbol();
    }
    ret += "]";
    return ret;
  }
  string value() const
  {
    string ret = +"[";
    if (!_elements.empty())
    {
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end() - 1; ++it)
        ret += (*it)->value() + ", ";
      ret += (*it)->value();
    }
    ret += "]";
    return ret;
  }
  bool match(Term &term)
  {
  }
  bool match(List &list)
  {

    if (this == &list)
    {
      return true;
    }
    else
    {
      if (this->size() == list.size())
      {
        for (int i = 0; i < list.size(); i++)
        {
          if (_elements[i]->isNumber == true && list._elements[i]->isVariable == true)
          {
            // list._elements[i]->_symbol =_elements[i]->symbol();
            return true;
          }
          else if (_elements[i]->match(*list._elements[i]) == false)
          {
            return false;
          }
        }
        return true;
      }
      else
      {
        return false;
      }
    }
  }
  bool match(Variable &var)
  {
    for (int i = 0; i < this->size(); i++)
    {
      if (this->count(i).symbol() == var.symbol())
      {
        return false;
      }
    }

    if (!var._inst)
    {
      var._inst = this;
      return true;
    }
    return var._inst->match(*this);
  }

public:
  List() : _elements()
  {
    isList = true;
  }
  List(vector<Term *> const &elements) : _elements(elements)
  {
    isList = true;
  }
  Term *head() const
  {
    if (_elements.size() == 0)
    {
      throw string("Accessing head in an empty list");
    }
    return _elements[0];
  }
  List *tail() const
  {
    if (_elements.size() == 0)
    {
      throw string("Accessing tail in an empty list");
    }

    List *ls;
    vector<Term *> args;
    for (int i = 1; i < _elements.size(); i++)
    {
      args.push_back(_elements[i]);
    }
    ls = new List(args);
    return ls;
  }
  int size()
  {
    return _elements.size();
  }
  Term count(int &i)
  {
    return *_elements[i];
  }
  vector<Term *> _elements;

private:
};
#endif
