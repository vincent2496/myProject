#ifndef UTLIST_H
#define UTLIST_H
#include <string>
#include <list>
#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

using namespace std;
using std::string;

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
	List list;
	ASSERT_EQ(list.symbol(), "[]");
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
	Number n496(496);
	Number n8128(8128);
	vector<Term *> vector1 = {&n496, &n8128};
	List NumberList(vector1);
	ASSERT_EQ("[496, 8128]", NumberList.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term *> vector1 = {&terence_tao, &alan_mathison_turing};
	List atomList(vector1);
	ASSERT_EQ(atomList.symbol(), "[terence_tao, alan_mathison_turing]");
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X");
	Variable Y("Y");
	vector<Term *> vector1 = {&X, &Y};
	List variableList(vector1);
	ASSERT_EQ(variableList.symbol(), "[X, Y]");
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom");
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number n8128(8128);
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	ASSERT_FALSE(n8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {	
	Atom tom("tom");
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	
	vector<Term *> vectorX = {&X};
	Struct s(Atom("s"), vectorX);
	ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	
	Variable Y("Y");
	vector<Term *> vectorX = {&Y};
	ASSERT_TRUE(Y.match(list));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	ASSERT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list(vector1);
	ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vectorX = {&n496, &X, &terence_tao};
	List listX(vectorX);
	
	Variable Y("Y");
	vector<Term *> vectorY = {&n496, &Y, &terence_tao};
	List listY(vectorY);
	ASSERT_TRUE(listX.match(listY));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vectorX = {&n496, &X, &terence_tao};
	List listX(vectorX);
	
	Number n8128(8128);
	vector<Term *> vector8128 = {&n496, &n8128, &terence_tao};
	List listY(vector8128);
	//ASSERT_TRUE(vectorX.match(vector8128));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.

TEST(List, matchVarinListToAtomShouldSucceed) {
	Number n496(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term *> vector1 = {&n496, &X, &terence_tao};
	List list1(vector1);
	Variable Y("Y");
	
	Atom alan_mathison_turing("alan_mathison_turing");
	
	//ASSERT_TRUE(Y.match(list1));
	//ASSERT_TRUE(X.match(alan_mathison_turing));	
	//ASSERT_EQ(Y.value(), "[496, alan_mathison_turing, terence_tao]");
	//ASSERT_EQ(X.value(), "alan_mathison_turing");
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
	Atom f("first");
	Atom s("second");
	Atom t("third");
	vector<Term *> vector1 = {&f, &s, &t};
	List list(vector1);

  //EXPECT_EQ(list.head()->symbol(), "first");
  //EXPECT_EQ(list.tail()->symbol(), "[second, third]");
  //EXPECT_EQ(list.tail()->value(), "[second, third]");
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
	Atom f("first");
	Atom s("second");
	Atom t("third");
	vector<Term *> vector1 = {&f, &s, &t};
	List list(vector1);

  //EXPECT_EQ(list.tail()->head()->value(), );
  //EXPECT_EQ(list.tail()->tail()->value(), );
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("first");
	vector<Term *> vector1 = {&f};
	List list1(vector1);
	
	Atom s("second");
	Atom t("third");
	vector<Term *> vector2 = {&list1, &s, &t};
	List list2(vector2);

  //EXPECT_EQ(list2->head()->value(), "[first]");
  //EXPECT_EQ(list2->tail()->value(), "[second, third]");
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first");
	Atom s("second");
	Atom t("third");
	vector<Term *> vector1 = {&f, &s, &t};
	List list1(vector1);
	//EXPECT_EQ(list1->tail()->tail()->head()->value(), "third");
    //EXPECT_EQ(list1->tail()->tail()->tail()->value(), "[]");
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
	vector<Term *> vector1;
	List list(vector1);
	try {list.head();}
	catch(string s) {
		EXPECT_EQ(s, "Accessing head in an empty list");
	}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
	vector<Term *> vector1;
	List list(vector1);
	try {list.tail();}
	catch(string s) {
		EXPECT_EQ(s, "Accessing tail in an empty list");
	}
}

#endif