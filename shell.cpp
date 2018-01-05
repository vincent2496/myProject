#include "parser.h"
#include "scanner.h"

#include <iostream>

using namespace std;
int main( int argc , char **argv )
{
    string input = "";
    string text = "";
    Parser* pParser;
	//infinity loop
    while(true)
	{
        while(input == "" || text.back() != '.')
		{
			if(text == "")
                cout<<"?- ";
            else cout<<"|  ";
            getline(cin, input);
			
            if(input != "")
		    {
                while(input[0] == ' '){
                    input = input.substr(1,input.size()-1);
                }
            text+=input;
            }
		}
		
        if(text=="halt.") 
			break;

        Scanner s(text);
        Parser pParser(s);
		
        pParser.buildExpression();
        Exp* pExp = pParser.getExpressionTree();
        pExp->evaluate();
		
        string result = pExp->value() + '.';
        //cout << result << endl;
        cout << result << endl;
        //text = "";
		text = "";
    };
}