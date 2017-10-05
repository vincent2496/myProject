#ifndef UTTERM_H
#define UTTERM_H

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "number.h"
#include "atom.h"
#include "variable.h"

using namespace std;

const double _epsilon = 0.01;

//test Number.value()
TEST (Number,ctor) {
    Number n(0);
    ASSERT_EQ("0", n.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number n(0);
	ASSERT_EQ("0", n.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number n_right(25);
	Number n_left(25);
	ASSERT_TRUE(n_right.match(n_left));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number n_right(25);
	Number n_left(0);
	ASSERT_FALSE(n_right.match(n_left));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number n(25);
	Atom a("tom");
    ASSERT_FALSE(n.match(a));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number n(25);
	Variable v("X");
    ASSERT_TRUE(n.match(v));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom a("tom");
	Number n(25);
    ASSERT_FALSE(a.match(n));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom atom("tom");
	Variable variable("X");
	ASSERT_TRUE(atom.match(variable));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Variable variable("X");
	Atom atom("tom");
	ASSERT_TRUE(variable.match(atom));
	ASSERT_TRUE(atom.match(variable));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable variable("X");
	Atom atom_jerry("jerry");
	Atom atom_tom("tom");
	ASSERT_TRUE(variable.match(atom_jerry));
	ASSERT_FALSE(atom_tom.match(variable));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable variable("X");
	Number number(5);
	ASSERT_TRUE(variable.match(number));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable variable("X");
	Number number_25(25);
	Number number_100(100);
	variable.match(number_25);
	ASSERT_FALSE(variable.match(number_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable variable("X");
	Atom atom("tom");
	Number number(25);
	variable.match(atom);
	ASSERT_FALSE(variable.match(number));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Atom atom("tom");
	Variable variable("X");
	Number number(25);
	atom.match(variable);
	ASSERT_FALSE(number.match(variable));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Variable variable("X");
	Atom atom("tom");
	variable.match(atom);
	ASSERT_TRUE(variable.match(atom));
}
#endif
