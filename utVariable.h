#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"


TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
Variable X("X");
  Number num(2.7182);
  X.match(num);
  ASSERT_EQ("2.7182", X.value());

}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
	Variable variable1("X");
    Variable variable2("Y");
	variable1.match(variable2);

	Number number1(1);
    variable1.match(number1);
    ASSERT_EQ(variable1.value(), "1");
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
	Variable variable1("X");
    Variable variable2("Y");
	variable1.match(variable2);

	Number number1(1);
    variable2.match(number1);
    ASSERT_EQ(variable2.value(), "1");
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
	Variable variable("X");
    Number number1(1);
    variable.match(variable);
    variable.match(number1);
    ASSERT_EQ(variable.value(), "1");
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
    Variable variable2("Y");
	Number number1(1);
	variable2.match(number1);
	Variable variable1("X");
    variable1.match(variable2);
    ASSERT_EQ(variable1.value(), "1");
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
	Variable variableX("X");
    Variable variableY("Y");
    variableX.match(variableY);

	Variable variableZ("Z");
	variableY.match(variableZ);

	Number number1(1);
	variableZ.match(number1);

    ASSERT_EQ(variableX.value(), "1");
    ASSERT_EQ(variableY.value(), "1");
    ASSERT_EQ(variableZ.value(), "1");
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
	Variable variableX("X");
    Variable variableY("Y");
    variableX.match(variableY);

	Variable variableZ("Z");
	variableX.match(variableZ);

	Number number1(1);
	variableZ.match(number1);

    ASSERT_EQ(variableX.value(), "1");
    ASSERT_EQ(variableY.value(), "1");
    ASSERT_EQ(variableZ.value(), "1");
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
	Variable variableX("X");
    Variable variableY("Y");
    vector<Term *> v1 = {&variableX};

    Struct structS(Atom("s"),v1);
    variableY.match(structS);

	ASSERT_EQ("Y",Y.symbol());
    ASSERT_EQ("s(X)",Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
  Variable X("X");
  Variable Y("Y");
  Atom teddy("teddy");
  std::vector<Term *> v={&X};
  Struct s(Atom("s"),v);
  teddy.match(X);
  Y.match(s);
  ASSERT_EQ("Y", Y.symbol());
  ASSERT_EQ("s(teddy)", Y.value());
}

#endif
