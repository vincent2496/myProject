#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"
#include <iostream>
using namespace std;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      if(_terms.size() > 0){
        for(int i = findFlag; i < _terms.size(); i++){
          if(_terms[i]->symbol() == symtable[_scanner.tokenValue()].first) return _terms[i];
          else if(dynamic_cast<Struct*>(_terms[i]) != 0){
            Struct * s = dynamic_cast<Struct*>(_terms[i]);
            for(int j = 0; j < s->arity(); j++){
              if(s->args(j)->symbol() == symtable[_scanner.tokenValue()].first){
                return s->args(j);
              }
            }
          }
        }
      }
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  void matchings() {
    findFlag = 0;
    vector<Node *> nodes;
    while(_currentToken != ATOMSC) {
      _terms.push_back(createTerm());
      Node * leftNode = new Node(TERM,  _terms[_terms.size()-1], 0, 0);
      switch(_scanner.nextToken()){
        case '=':
          _terms.push_back(createTerm());
          nodes.push_back(new Node(EQUALITY, 0, leftNode, new Node(TERM, _terms[_terms.size()-1], 0, 0)));
          break;
        case ',':
          nodes.push_back(new Node(COMMA));
          break;
        case ';':
          nodes.push_back(new Node(SEMICOLON));
          break;
        case ATOMSC:
          _currentToken = ATOMSC;
          break;
      }
      switch(_scanner.nextToken()) {
        case ',' :
          nodes.push_back(new Node(COMMA, 0, nodes[nodes.size()-1], 0));
          _currentToken = ',';
          break;
        case ';' :
          nodes.push_back(new Node(SEMICOLON, 0, nodes[nodes.size()-1], 0));
          _currentToken = ';';
          findFlag = _terms.size();
          break;
        case ATOMSC:
          if(nodes.size() == 1) _root = nodes[0];
          else{
            nodes[nodes.size()-2]->right = nodes[nodes.size()-1];
            for(int i = nodes.size()-2; i > 1; i-=2){
              if(i - 2 > 0) nodes[i-2]->right = nodes[i];
            }
            _root = nodes[1];
          }
          _currentToken = ATOMSC;
          break;
      }
    }
  }

  Node * expressionTree() {
    return _root;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest, ListOfTermsEmpty);
  FRIEND_TEST(ParserTest, listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node * _root;
  int findFlag;
};
#endif
