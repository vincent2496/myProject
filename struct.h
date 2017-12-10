#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
// #include "iterator.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// class Number;
// class variable;
// class Iterator;

// template <class T> 
// class Iterator;

class Struct : public Term
{
public:
    Struct(Atom const & name, std::vector<Term *> args);
    Term * args(int index);
    Atom const & name();
    string symbol() const;
    string value() const;
    bool match(Term &term);
	int arity();
	//Iterator * createIterator();
public:	
	Iterator<Term *> * createDFSIterator();
    Iterator<Term *> * createBFSIterator();
	Iterator<Term*> * createIterator();
	vector<Term *> BFS();
    vector<Term *> DFS(); 
	void recursiveofDFS(Struct *s , stack<Term*> &s_t , vector<Term*> &v);
    void recursiveofDFS(List *l ,  stack<Term*> &s_t , vector<Term*> &v);
private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
