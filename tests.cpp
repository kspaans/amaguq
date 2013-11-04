#include "gtest/gtest.h"

#include <string>
#include "amaguq.h"

struct ints_test : testing::Test {
	amaguq a;
	atom *t;
	fixnum *i;
};

TEST_F(ints_test, integers0)
{
	std::string s = "123";

	t = a.eval(s);
	i = dynamic_cast<fixnum *>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(123, i->value);
}

TEST_F(ints_test, integers1)
{
	std::string s = "-123";

	t = a.eval(s);
	i = dynamic_cast<fixnum *>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(-123, i->value);
}

TEST_F(ints_test, integers2)
{
	std::string s = "007";

	t = a.eval(s);
	i = dynamic_cast<fixnum *>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(7, i->value);
}
