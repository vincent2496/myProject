#include "list.h"
#include "iterator.h"

Iterator<Term *> * List::createIterator(){
    return new ListIterator<Term *>(this);
}

Iterator<Term *> * List::createBFSIterator (){
    vector <Term *> BFSvec = this->BFS();
    return new BFSIterator<Term *>(BFSvec);
}

vector<Term *> List::BFS(){
    queue <Term *> q ;
    vector<Term *> v ;
    List *isList;  
    Struct *isStruct;
	
    for(int i = 0  ;  i < this->arity() ; i ++){
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

vector<Term *> List::DFS(){
    stack <Term *> s_t;
    vector<Term *> v ;
    List *isList;
	
    Struct *isStruct; 
	
    for(int i = 0  ;  i < this->arity() ; i ++){
      s_t.push(this->args(i));      
      isStruct = dynamic_cast<Struct*>(s_t.top());
      isList = dynamic_cast<List*> (s_t.top());    
      v.push_back(s_t.top());
      if(isStruct){
        recursiveDFS(isStruct,s_t,v);    
      }
      else if(isList){
        recursiveDFS(isList,s_t,v); 
      }
      s_t.pop();
    }
  return v;
}

Iterator<Term*>* List::createDFSIterator(){
    vector<Term*> DFSvec = this->DFS();
    return new DFSIterator<Term *>(DFSvec);
}

void List::recursiveDFS(List *l , stack<Term *> &s_t , vector<Term *> &v){
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

void List::recursiveDFS(Struct *s, stack<Term *> &s_t, vector<Term *> &v){
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

string List::symbol() const{
	string ret = "[";
	
	if(_elements.empty()){
        ret = ret + "]";
    }
	else{
		for(int i=0; i<_elements.size(); i++){
			ret = ret + _elements[i]->symbol();		
			if(i<_elements.size()-1){ret = ret + ", ";}
			}
		ret = ret + "]";	
	}
	return ret;
}

string List::value() const{
	string ret = "[";
	
	if(_elements.empty()){
        ret = ret + "]";
    }
	else{
		for(int i=0; i<_elements.size(); i++){
			ret = ret + _elements[i]->value();		
			if(i<_elements.size()-1){ret = ret + ", ";}			
		}		
		ret = ret + "]";	
	}
	return ret;
}

Term * List::head() const{	
    if(_elements.size() < 1)
    {
        string s = "Accessing head in an empty list";
        throw s;
    }
    return _elements[0];
}

List * List::tail() const
{
    if(_elements.size() < 1)
    {
        string s = "Accessing tail in an empty list";
        throw s;

    }
    vector<Term *> vector1 = _elements;
    vector1.erase(vector1.begin());
    List * tail1 = new List(vector1);
    return tail1;
}

bool List::match(Term & term){
    List * pl = dynamic_cast<List *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);

    bool ret = true;
    if(pl){
        if(_elements.size() != pl->elements().size()){       
		ret = false;
        }else
		{
            for(int i = 0; i < _elements.size(); i++){
                if(_elements[i]->match( *(pl->elements()[i]) )!=true)
				{ret = true;}
            }
        }
    }
    else if(pv){
        ret = pv->match(*this);
    }
    else{
        ret = false;
    }
    return ret;

}

Term * List::args(int i)
{
    return _elements[i];
}

int List::length() const
{
    return _elements.size();
}

vector<Term *> List::elements(){
    return _elements;
}

int List::arity() const {
	return _elements.size();
}