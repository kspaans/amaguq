#include "gtest/gtest.h"

#include <string>
#include "amaguq.h"

struct ints_test : testing::Test {
	amaguq a;
	atom* t;
	fixnum* i;
};

struct bools_test : testing::Test {
	amaguq a;
	atom* t;
	boolean* b;
};

struct chars_test : testing::Test {
	amaguq a;
	atom* t;
	charlit* c;
};

struct strings_test : testing::Test {
	amaguq a;
	atom* t;
	strlit* s;
};

struct lists_test : testing::Test {
	amaguq a;
	atom* t;
	list* l;
};

TEST_F(ints_test, integers0)
{
	std::string s = "123";

	t = a.eval(s);
	i = dynamic_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(FIXNUM, i->atype);
	EXPECT_EQ(123, i->value);
}

TEST_F(ints_test, integers1)
{
	std::string s = "-123";

	t = a.eval(s);
	i = dynamic_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(-123, i->value);
}

TEST_F(ints_test, integers2)
{
	std::string s = "007";

	t = a.eval(s);
	i = dynamic_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(7, i->value);
}

TEST_F(bools_test, booleans0)
{
	std::string s = "#t";

	t = a.eval(s);
	b = dynamic_cast<boolean*>(t);
	EXPECT_NE(nullptr, b);
}

TEST_F(bools_test, booleans1)
{
	std::string s = "#f";

	t = a.eval(s);
	b = dynamic_cast<boolean*>(t);
	EXPECT_NE(nullptr, b);
}

TEST_F(bools_test, booleans_singletons)
{
	std::string tr = "#t";
	std::string f  = "#f";
	atom* t2;
	atom* t3;
	atom* t4;

	t = a.eval(tr);
	t2 = a.eval(tr);
	t3 = a.eval(f);
	t4 = a.eval(f);
	EXPECT_EQ(t, t2);
	EXPECT_EQ(t3, t4);
}

TEST_F(chars_test, chars0)
{
	std::string s = "#\\a";

	t = a.eval(s);
	c = dynamic_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ(s, c->str);
}

TEST_F(chars_test, chars1)
{
	std::string s = "#\\ ";

	t = a.eval(s);
	c = dynamic_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ("#\\space", c->str);
}

TEST_F(chars_test, chars2)
{
	std::string s = "#\\\n";

	t = a.eval(s);
	c = dynamic_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ("#\\newline", c->str);
}

TEST_F(strings_test, str0)
{
	std::string str = "\"asdf\"";

	t = a.eval(str);
	s = dynamic_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(strings_test, str1)
{
	std::string str = "\"asdf\\\"asdf\"";

	t = a.eval(str);
	s = dynamic_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(strings_test, str2)
{
	std::string str = "\"asdf\\n\"";

	t = a.eval(str);
	s = dynamic_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(lists_test, list0)
{
	std::string s = "()";

	t = a.eval(s);
	l = dynamic_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(a.hp.h[2], l);
}

TEST_F(lists_test, list1)
{
	std::string s = "(0 . 1)";
	fixnum* i1;
	fixnum* i2;

	t = a.eval(s);
	l = dynamic_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	i1 = reinterpret_cast<fixnum*>(l->car);
	i2 = reinterpret_cast<fixnum*>(l->cdr);
	EXPECT_EQ(0, i1->value);
	EXPECT_EQ(1, i2->value);
}

TEST_F(lists_test, listints)
{
	std::string s = "(4567 . 13)";
	fixnum* i1;
	fixnum* i2;

	t = a.eval(s);
	l = dynamic_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	i1 = reinterpret_cast<fixnum*>(l->car);
	i2 = reinterpret_cast<fixnum*>(l->cdr);
	EXPECT_EQ(4567, i1->value);
	EXPECT_EQ(13, i2->value);
}

TEST_F(lists_test, listchars)
{
	std::string s = "(#\\k . #\\j)";
	charlit* c1;
	charlit* c2;

	t = a.eval(s);
	l = dynamic_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	c1 = reinterpret_cast<charlit*>(l->car);
	c2 = reinterpret_cast<charlit*>(l->cdr);
	//EXPECT_EQ("#\\k", c1->str);
	//EXPECT_EQ("#\\j", c2->str);
}

TEST_F(lists_test, list0empty)
{
	std::string s = "(0 . ())";
	fixnum* i1;
	list* l2;

	t = a.eval(s);
	EXPECT_EQ(LIST, t->atype);
	l = reinterpret_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(FIXNUM, l->car->atype);
	EXPECT_EQ(LIST, l->cdr->atype);
	i1 = reinterpret_cast<fixnum*>(l->car);
	l2 = reinterpret_cast<list*>(l->cdr);
	EXPECT_EQ(FIXNUM, i1->atype);
	EXPECT_EQ(0, i1->value);
	EXPECT_EQ(LIST, l2->atype);
	EXPECT_EQ(a.hp.h[2], l2);
}

TEST_F(lists_test, list0empty2)
{
	std::string s = "(0 ())";
	fixnum* i1;
	list* l2;

	t = a.eval(s);
	EXPECT_EQ(LIST, t->atype);
	l = reinterpret_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(FIXNUM, l->car->atype);
	EXPECT_EQ(LIST, l->cdr->atype);
	i1 = reinterpret_cast<fixnum*>(l->car);
	l2 = reinterpret_cast<list*>(l->cdr);
	EXPECT_EQ(FIXNUM, i1->atype);
	EXPECT_EQ(0, i1->value);
	EXPECT_EQ(LIST, l2->atype);
	EXPECT_EQ(a.hp.h[2], l2);
}
