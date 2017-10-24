#include "list.h"

string List::symbol() const{
	string ret = "[";
	
	if(_elements.empty()){
        ret = ret + "]";
    }
	else{
		for(int i = 0; i<_elements.size(); i++){
			ret = ret + _elements[i]->symbol() + ", ";
		}
		ret = ret + _elements[_elements.size()-1]->symbol() + "]";
	}
	return ret;
}

string List::value() const{
	string ret = "[";
	
	if(_elements.empty()){
        ret = ret + "]";
    }
	else{
		for(int i = 0; i<_elements.size(); i++){
			ret = ret + _elements[i]->symbol() + ", ";
		}
		ret = ret + _elements[_elements.size()-1]->symbol() + "]";
	}
	return ret;
}

bool List::match(Term & term){
	
	
	
}

Term * List::head() const{
	/*
	if(_elements.size()){
	    return "Accessing head in an empty list";	
	}
	*/
}

List * List::tail() const{
	
}