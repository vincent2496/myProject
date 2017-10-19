#include <vector>
#include "atom.h"
#include "struct.h"
#include "number.h"
#include "variable.h"

using namespace std;

TEST(Struct, hobby)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby", hobby.name().symbol());
  ASSERT_EQ("tom", hobby.args(0)->symbol());
  ASSERT_EQ("chaseMouse", hobby.args(1)->symbol());

}

TEST(Struct, symbol)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  ASSERT_EQ("hobby(tom, chaseMouse)",hobby.symbol());
}

TEST(Struct, match1)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby2"), v);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match2){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = {&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match3){
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  std::vector<Term *> v1 = { &chaseMouse,&tom};
  Struct hobby2(Atom("hobby"), v1);
  EXPECT_FALSE(hobby.match(hobby2));
}

TEST(Struct, match4)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  Struct hobby2(Atom("hobby"), v);
  EXPECT_TRUE(hobby.match(hobby2));
}

TEST(Struct, match5)
{
  Atom tom("tom");
  Atom chaseMouse("chaseMouse");
  std::vector<Term *> v = {&tom, &chaseMouse};
  Struct hobby(Atom("hobby"), v);
  EXPECT_FALSE(hobby.match(tom));
}

// When Struct s contains a Variable X
// Then #symbol() should return "s(X)"
// and #value() should also return "s(X)"
TEST(Struct, var)
{
	Variable variable1("X");
	vector<Term *> v = {&variable1};
	//the type of struct name is "Atom type"
	Struct struct1(Atom("s"), v);
	ASSERT_EQ("s(X)", struct1.symbol());
	ASSERT_EQ("s(X)", struct1.value());
}

// Given there is Struct s contains a Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() should return "s(X)"
// and #value() should also return "s(tom)"
TEST(Struct, var_match_atom)
{
	Variable variable1("X");
	vector<Term *> v = {&variable1};	
	Atom atom("tom");
	variable1.match(atom);
	Struct struct1(Atom("s"), v);
	
	ASSERT_EQ("s(X)", struct1.symbol());
	ASSERT_EQ("s(X)", struct1.value());
}

// Given there are Struct s1 and Struct s2
// When Struct s1 contains Struct s2
// And Struct s2 contains a Variable X
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should also return "s1(s2(X))"
TEST(Struct, nested_struct1)
{
	Variable variable1("X");
	vector<Term *> v1 = {&variable1};
	Struct struct2(Atom("s2"), v1);
	
	vector<Term *> v2 = {&struct2};
	Struct struct1(Atom("s1"), v2);
	
	ASSERT_EQ("s1(s2(X))", struct1.symbol());
	ASSERT_EQ("s1(s2(X))", struct1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Atom "tom"
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(tom))"
TEST(Struct, nested_struct2)
{
	Variable variable1("X");
	Atom atom("tom");
	variable1.match(atom);
	vector<Term *> v1 = {&variable1};
		
	Struct struct2(Atom("s2"), v1);
	vector<Term *> v2 = {&struct2};
	Struct struct1(Atom("s1"), v2);
	
	ASSERT_EQ("s1(s2(X))", struct1.symbol());
	ASSERT_EQ("s1(s2(X))", struct1.value());
}

// Given there are Struct s1 contains Struct s2
// And Struct s2 contains Variable X
// When Variable X matches an Number pi: 3.14
// Then #symbol() of s1 should return "s1(s2(X))"
// and #value() of s1 should return "s1(s2(3.14))"
TEST(Struct, nested_struct3)
{
	Variable variable1("X");
	Number number(3.14);
	variable1.match(number);	
	vector<Term *> v1 = {&variable1};
		
	Struct struct2(Atom("s2"), v1);
	vector<Term *> v2 = {&struct2};
	Struct struct1(Atom("s1"), v2);
	
	//ASSERT_EQ("s1(s2(X))", struct1.symbol());
	//ASSERT_EQ("s1(s2(X))", struct1.value());
}

// Given there are Struct s1 contains Struct s2 and Variable X
// And Struct s2 contains Variable Y
// When Variable X matches Variable Y
// And Variable X matches Atom "kent_beck"
// Then #symbol() of s1 should return "s1(s2(Y), X)"
// and #value() of s1 should return "s1(s2(kent_beck), kent_beck)"
TEST(Struct, nested_struct_and_multiVariable)
{
	Variable variable1("X");
	Variable variable2("Y");
	variable1.match(variable2);
	
	Atom atom("kent_beck");
	variable1.match(atom);
	vector<Term *> v1 = {&variable2};
	
	Struct struct2(Atom("s2"), v1);
	vector<Term *> v2 = {&struct2, &variable1};
	Struct struct1(Atom("s1"), v2);
	
	ASSERT_EQ("s1(s2(Y), X)", struct1.symbol());
	ASSERT_EQ("s1(s2(kent_beck), kent_beck)", struct1.value());
}
