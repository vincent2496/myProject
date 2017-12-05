#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List list;
  ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
  Number _8128(8128);
  Number _496(496);
  vector<Term *> terms = {&_8128, &_496};
  List list(terms);

  ASSERT_EQ("[8128, 496]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  vector<Term *> terms = { &terence_tao, &alan_mathison_turing };
  List list(terms);

  ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  vector<Term *> terms = { &X, &Y };
  List list(terms);

  ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms = {  &_496, &X, &terence_tao };
  List list(terms);

  ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number _8128(8128);
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms = {  &_496, &X, &terence_tao };
  List list(terms);

  ASSERT_FALSE(_8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms = {  &_496, &X, &terence_tao };
  vector<Term *> v = { &X };
  Struct s(Atom("s"), v);
  List list(terms);

  ASSERT_FALSE(list.match(s));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  Variable Y("Y");
  vector<Term *> terms = { &_496, &X, &terence_tao };
  List list(terms);

  //ASSERT_TRUE(Y.match(list));
  ASSERT_TRUE(list.match(Y));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms = {  &_496, &X, &terence_tao };
  List list(terms);

  ASSERT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) 
{
  Number _496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms = {  &_496, &X, &terence_tao };

  List list(terms);
  ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  vector<Term *> terms1 = {  &_496, &X, &terence_tao };
  vector<Term *> terms2 = {  &_496, &Y, &terence_tao };

    List list1(terms1);
    List list2(terms2);
  
  ASSERT_TRUE(list1.match(list2));
  ASSERT_EQ("[496, Y, terence_tao]", list1.value());
  ASSERT_EQ("[496, Y, terence_tao]", list2.value());
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number _496(496);
  Number _8128(8128);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> terms1 = {  &_496, &X, &terence_tao };
  vector<Term *> terms2 = {  &_496, &_8128, &terence_tao };

  List list1(terms1);
  List list2(terms2);
  ASSERT_TRUE(list1.match(list2));
  ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  vector<Term *> terms = {  &_496, &X, &terence_tao };
  List list(terms);
  ASSERT_TRUE(Y.match(list));
  ASSERT_TRUE(X.match(alan_mathison_turing));
  ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
  ASSERT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = first, T = [[second], third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> arg1 = {&f};
  List list1(arg1);
  vector<Term *> arg2 = {&list1, &s, &t};
  List list2(arg2);

  EXPECT_EQ(string("[first]"), list2.head()->value());
  EXPECT_EQ(string("[second, third]"), list2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  vector<Term *> args;
  List l(args);
  try {
    l.head();
  }
  catch(string msg) {
    EXPECT_EQ(string("Accessing head in an empty list"), msg);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  vector<Term *> args;
  List l(args);
  try {
    l.tail();
  }
  catch(string msg) {
    EXPECT_EQ(string("Accessing tail in an empty list"), msg);
  }
}

#endif
