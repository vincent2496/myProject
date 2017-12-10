#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"
#include <vector>
#include <string>
#include <stack>

using std::vector;
using namespace std;

class Struct;

class List : public Term{
public:
    bool match(Term & term);
    List (): _elements(0) {}
    List (vector<Term *> const & elements):_elements(elements){}
	vector<Term *> elements();
    string symbol() const;
    string value() const;
    Term * head() const;
    List * tail() const;
	Term * args(int i);
    int length() const;
	int arity() const;
private:
    vector<Term *> _elements;
public:
	Iterator<Term *> * createDFSIterator();
    Iterator<Term *> * createBFSIterator();
	Iterator<Term *> * createIterator();
	vector<Term *> DFS(); 
	vector<Term *> BFS();
    void recursiveofDFS(Struct *s , stack<Term*> &s_t , vector<Term*> &v);
    void recursiveofDFS(List *l ,  stack<Term*> &s_t , vector<Term*> &v);	
};

#endif