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
			ret = ret + _elements[i]->symbol();		
			if(i<_elements.size()-1){ret = ret + ", ";}
			}
		ret = ret + "]";	
	}
	return ret;
}

bool List::match(Term & term){
	
	
	
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