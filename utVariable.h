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
	Atom atom("X");
	Number number(2.7182);
	atom.match(number);
	//ASSERT_EQ(atom.value(), "2.7182");
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
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  X.match(Y);
  Y.match(Z);
  Number num(1);
  Z.match(num);
  ASSERT_EQ("1", X.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  X.match(Y);
  X.match(Z);
  Number num(1);
  Z.match(num);
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
  Variable X("X");
  Variable Y("Y");
  Variable Z("Z");
  X.match(Y);
  X.match(Z);
  Number num(1);
  Z.match(num);
  ASSERT_EQ("1", X.value());
  ASSERT_EQ("1", Y.value());
  ASSERT_EQ("1", Z.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
    Variable X("X");
   Variable Y("Y");
   std::vector<Term *> v={&X};
   Struct s(Atom("s"),v);
   Y.match(s);
   ASSERT_EQ("Y", Y.symbol());
   ASSERT_EQ("s(X)", Y.value());
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

}


#endif
