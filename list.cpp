#include "list.h"

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