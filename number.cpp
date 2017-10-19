#include "number.h"
#include <string>
#include <sstream>

using namespace std;

string Number::symbol() const{
    return _symbol;
}

//Number::Number(string s):_symbol(s),_value(s){}


bool Number::match(Term &term){
	return true;
}

Number::Number(double i){
	_value = i;
	
	string s;
	stringstream ss(s);
	ss << i;
	_symbol = ss.str();
}
/*	
string Number::symbol(){
    return _symbol;
}
*/   
string Number::value(){
    string s;
	stringstream ss(s);
	ss << _value;
	return ss.str();
}
/*   
bool Number::match(Number number){
    return _value == number._value;
}
 
bool Number::match(Atom atom){
    return false;
}
*/ 
bool Number::match(Variable &variable){
    if(variable._assignable){    
        variable.match(*this);	
        variable._assignable = false;
	    return true;
    }
	else
        return _symbol == variable.value();
}
