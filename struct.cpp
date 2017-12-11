#include "struct.h"
#include "iterator.h"

Iterator<Term*> * Struct::createIterator(){
    return new StructIterator<Term *>(this);
}

Iterator<Term*> * Struct::createBFSIterator(){
  vector<Term*> BFSvec = this->BFS();
  return new BFSIterator<Term *>(BFSvec);
}

Iterator<Term*> * Struct::createDFSIterator(){
  vector<Term*> DFSvec = this->DFS();
  return new DFSIterator<Term *>(DFSvec);
}

void Struct::recursiveDFS(List *l, stack<Term *> &s_t, vector<Term *> &v){
    List *isList;  
    Struct *isStruct;  
    for(int i=0;  i<l->arity(); i++){
      s_t.push(l->args(i));      
      v.push_back(s_t.top());
	  
      isList = dynamic_cast<List*>(s_t.top());
      isStruct = dynamic_cast<Struct*>(s_t.top());
	  
      if(isList){recursiveDFS(isList, s_t, v);}
      else if(isStruct){recursiveDFS(isStruct, s_t, v);}
      s_t.pop();
    }
}

void Struct::recursiveDFS(Struct *s, stack<Term *> &s_t, vector<Term *> &v){
    List *isList;  
    Struct *isStruct; 
    for(int i=0; i<s->arity(); i++){
      s_t.push(s->args(i));      
      v.push_back(s_t.top());
	  
      isList = dynamic_cast<List*>(s_t.top());
      isStruct = dynamic_cast<Struct*>(s_t.top());
	  
      if(isList){recursiveDFS(isList, s_t, v);}
      else if(isStruct){recursiveDFS(isStruct, s_t, v);}
      s_t.pop();
    }
 }

vector<Term *> Struct::BFS(){

    vector<Term *> v;
	queue <Term *> q;
	
    List *isList;  
    Struct *isStruct;
	
    for(int i=0;  i<this->arity(); i++){
      q.push(this->args(i));
    }
	
    while(!q.empty()){
      isStruct = dynamic_cast<Struct*> (q.front());
      isList = dynamic_cast<List *> (q.front());
	  
      if(isStruct){
        for(int i=0; i<isStruct->arity(); i++){
          q.push(isStruct->args(i));
        }
      }
      else if(isList){
        for(int i=0; i<isList->arity(); i++){
          q.push(isList->args(i));
        }
      }
    v.push_back(q.front());
    q.pop();
  }
  return v;
}

vector<Term *> Struct::DFS(){
    stack <Term *> s_t;
    vector<Term *> v;
    List *isList;  
    Struct *isStruct; 
	
    for(int i=0; i<this->arity(); i++){
      s_t.push(this->args(i));      
      isStruct = dynamic_cast<Struct*>(s_t.top());
      isList = dynamic_cast<List*> (s_t.top());    
      v.push_back(s_t.top());
	  
      if(isStruct){recursiveDFS(isStruct,s_t,v);}
      else if(isList){recursiveDFS(isList,s_t,v);}
      s_t.pop();
    }
  return v;
}

Struct::Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {}

Term * Struct::args(int index) {
    return _args[index];
}

Atom const & Struct::name() {
    return _name;
}
  
int Struct::arity() {
    return _args.size();
}
	
string Struct::symbol() const{

    string ret =_name.symbol() + "(";
	
	if (_args.empty()){
      ret += ")";
      return ret;
    }
	
    for(int i = 0; i<_args.size()-1; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]->symbol() + ")";
    return  ret;
}
  
string Struct::value() const{

    string ret =_name.value() + "(";
	
	if (_args.empty()){
      ret += ")";
      return ret;
    }
	
    for(int i = 0; i<_args.size()-1; i++){
      ret += _args[i]-> value() + ", ";
    }

    ret += _args[_args.size()-1]->value() + ")";
    return  ret;
}
  
bool Struct::match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size() != ps->_args.size())
        return false;
      for(int i=0; i<_args.size(); i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
}


