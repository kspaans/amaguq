#include "gtest/gtest.h"

#include <string>
#include "amaguq.h"

struct ints_test : testing::Test {
	amaguq a;
	atom* t;
	fixnum* i;
	atom* a2;
};

struct bools_test : testing::Test {
	amaguq a;
	atom* t;
	boolean* b;
	atom* a2;
};

struct chars_test : testing::Test {
	amaguq a;
	atom* t;
	charlit* c;
	atom* a2;
};

struct strings_test : testing::Test {
	amaguq a;
	atom* t;
	strlit* s;
	atom* a2;
};

struct lists_test : testing::Test {
	amaguq a;
	atom* t;
	list* l;
	atom* a2;
};

struct symbols_test : testing::Test {
	amaguq a;
	atom* t;
	symbol* sy;
	atom* a2;
};

struct quote_test : testing::Test {
	amaguq a;
	atom* t;
};

struct env_test : testing::Test {
	amaguq a;
	atom *t;
	table::iterator it;
};

TEST_F(ints_test, integers0)
{
	std::string s = "123";

	t = a.read(s);
	i = static_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(FIXNUM, i->atype);
	EXPECT_EQ(123, i->value);
}

TEST_F(ints_test, ints_self_eval)
{
	std::string s = "74621";

	t = a.read(s);
	a2 = t->eval();
	EXPECT_EQ(a2, t);
	EXPECT_EQ("74621", a2->print());
}

TEST_F(ints_test, integers1)
{
	std::string s = "-123";

	t = a.read(s);
	i = static_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(-123, i->value);
}

TEST_F(ints_test, integers2)
{
	std::string s = "007";

	t = a.read(s);
	i = static_cast<fixnum*>(t);
	EXPECT_NE(nullptr, i);
	EXPECT_EQ(7, i->value);
}

TEST_F(bools_test, booleans0)
{
	std::string s = "#t";

	t = a.read(s);
	b = static_cast<boolean*>(t);
	EXPECT_NE(nullptr, b);
}

TEST_F(bools_test, bools_self_eval)
{
	std::string s = "#t";

	t = a.read(s);
	a2 = t->eval();
	EXPECT_EQ(a2, t);
	EXPECT_EQ("#t", a2->print());
}

TEST_F(bools_test, booleans1)
{
	std::string s = "#f";

	t = a.read(s);
	b = static_cast<boolean*>(t);
	EXPECT_NE(nullptr, b);
}

TEST_F(bools_test, booleans_singletons)
{
	std::string tr = "#t";
	std::string f  = "#f";
	atom* t2;
	atom* t3;
	atom* t4;

	t = a.read(tr);
	t2 = a.read(tr);
	t3 = a.read(f);
	t4 = a.read(f);
	EXPECT_EQ(t, t2);
	EXPECT_EQ(t3, t4);
}

TEST_F(chars_test, chars0)
{
	std::string s = "#\\a";

	t = a.read(s);
	c = static_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ(s, c->str);
}

TEST_F(chars_test, chars_self_eval)
{
	std::string s = "#\\C";

	t = a.read(s);
	a2 = t->eval();
	EXPECT_EQ(a2, t);
	EXPECT_EQ("#\\C", a2->print());
}

TEST_F(chars_test, chars1)
{
	std::string s = "#\\ ";

	t = a.read(s);
	c = static_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ("#\\space", c->str);
}

TEST_F(chars_test, chars2)
{
	std::string s = "#\\\n";

	t = a.read(s);
	c = static_cast<charlit*>(t);
	EXPECT_NE(nullptr, c);
	EXPECT_EQ("#\\newline", c->str);
}

TEST_F(strings_test, str0)
{
	std::string str = "\"asdf\"";

	t = a.read(str);
	s = static_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(strings_test, strings_self_eval)
{
	std::string s = "\"elyK\"";

	t = a.read(s);
	a2 = t->eval();
	EXPECT_EQ(a2, t);
	EXPECT_EQ("\"elyK\"", a2->print());
}

TEST_F(strings_test, str1)
{
	std::string str = "\"asdf\\\"asdf\"";

	t = a.read(str);
	s = static_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(strings_test, str2)
{
	std::string str = "\"asdf\\n\"";

	t = a.read(str);
	s = static_cast<strlit*>(t);
	EXPECT_NE(nullptr, s);
	EXPECT_EQ(str, s->str);
}

TEST_F(lists_test, list0)
{
	std::string s = "()";

	t = a.read(s);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(a.hp.h[2], l);
}

TEST_F(lists_test, list_empty_doesnt_self_eval)
{
	std::string s = "()";

	t = a.read(s);
	// TODO not use exceptions for program errors
	EXPECT_THROW(a2 = t->eval(), std::logic_error);
}

TEST_F(lists_test, lists_dont_self_eval)
{
	std::string s = "(55 ())";

	t = a.read(s);
	// TODO not use exceptions for program errors
	EXPECT_THROW(a2 = t->eval(), std::logic_error);
}

TEST_F(lists_test, list1)
{
	std::string s = "(0 . 1)";
	fixnum* i1;
	fixnum* i2;

	t = a.read(s);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	i1 = static_cast<fixnum*>(l->car);
	i2 = static_cast<fixnum*>(l->cdr);
	EXPECT_EQ(0, i1->value);
	EXPECT_EQ(1, i2->value);
}

TEST_F(lists_test, listints)
{
	std::string s = "(4567 . 13)";
	fixnum* i1;
	fixnum* i2;

	t = a.read(s);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	i1 = static_cast<fixnum*>(l->car);
	i2 = static_cast<fixnum*>(l->cdr);
	EXPECT_EQ(4567, i1->value);
	EXPECT_EQ(13, i2->value);
}

TEST_F(lists_test, listchars)
{
	std::string s = "(#\\k . #\\j)";
	charlit* c1;
	charlit* c2;

	t = a.read(s);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	c1 = static_cast<charlit*>(l->car);
	c2 = static_cast<charlit*>(l->cdr);
	//EXPECT_EQ("#\\k", c1->str);
	//EXPECT_EQ("#\\j", c2->str);
}

TEST_F(lists_test, list0empty)
{
	std::string s = "(0 . ())";
	fixnum* i1;
	list* l2;

	t = a.read(s);
	EXPECT_EQ(LIST, t->atype);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(FIXNUM, l->car->atype);
	EXPECT_EQ(LIST, l->cdr->atype);
	i1 = static_cast<fixnum*>(l->car);
	l2 = static_cast<list*>(l->cdr);
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

	t = a.read(s);
	EXPECT_EQ(LIST, t->atype);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(FIXNUM, l->car->atype);
	EXPECT_EQ(LIST, l->cdr->atype);
	i1 = static_cast<fixnum*>(l->car);
	l2 = static_cast<list*>(l->cdr);
	EXPECT_EQ(FIXNUM, i1->atype);
	EXPECT_EQ(0, i1->value);
	EXPECT_EQ(LIST, l2->car->atype);
	l2 = static_cast<list*>(l2->car);
	EXPECT_EQ(a.hp.h[2], l2);
}

TEST_F(lists_test, list123)
{
	std::string s = "(1 . (2 . (3 . ())))";
	fixnum* i;
	list *l2;

	t = a.read(s);
	EXPECT_EQ(LIST, t->atype);
	l = static_cast<list*>(t);
	EXPECT_NE(nullptr, l);
	EXPECT_EQ(FIXNUM, l->car->atype);
	EXPECT_EQ(LIST, l->cdr->atype);
	i = static_cast<fixnum*>(l->car);
	EXPECT_EQ(FIXNUM, i->atype);
	EXPECT_EQ(1, i->value);
	l2 = static_cast<list*>(l->cdr);
	i = static_cast<fixnum*>(l2->car);
	EXPECT_EQ(FIXNUM, i->atype);
	EXPECT_EQ(2, i->value);
	l2 = static_cast<list*>(l2->cdr);
	i = static_cast<fixnum*>(l2->car);
	EXPECT_EQ(FIXNUM, i->atype);
	EXPECT_EQ(3, i->value);
	EXPECT_EQ(a.hp.h[2], l2->cdr);
}

TEST_F(symbols_test, symbolasdf)
{
	std::string s = "asdf";

	t = a.read(s);
	EXPECT_EQ(SYMBOL, t->atype);
	sy = static_cast<symbol*>(t);
	EXPECT_NE(nullptr, sy);
	EXPECT_EQ(SYMBOL, sy->atype);
	EXPECT_EQ(sy->sym, s);
}

TEST_F(symbols_test, symbol_not_self_eval)
{
	std::string s = "asymbol";

	t = a.read(s);
	EXPECT_THROW(a2 = t->eval(), std::logic_error);
}

#if 0
TEST_F(quote_test, quote_sym)
{
	// TODO how to handle this when the argument to quote is a list of length 1?
	// TODO is it different from quoting a list?
	std::string s = "(quote a)";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("a", t->print());
}
#endif

TEST_F(quote_test, quote_tick)
{
	std::string s = "'a";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("a", t->print());
}

TEST_F(quote_test, quote_fixnum)
{
	std::string s = "'1";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("1", t->print());
}

TEST_F(quote_test, quote_bool)
{
	std::string s = "'#f";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("#f", t->print());
}

TEST_F(quote_test, quote_char)
{
	std::string s = "'#\\^";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("#\\^", t->print());
}

TEST_F(quote_test, quote_string)
{
	std::string s = "'\"alpha to omega\"";

	t = a.read(s);
	t = t->eval();
	EXPECT_EQ("\"alpha to omega\"", t->print());
}

TEST_F(env_test, define0)
{
	std::string s = "(define a 0)";
	fixnum* i;
	list* l;

	t = a.read(s);
	EXPECT_EQ(t->atype, LIST);
	l = static_cast<list*>(t);
	EXPECT_EQ(l->car->atype, SYMBOL);
	EXPECT_EQ(l->cdr->atype, LIST);
	l = static_cast<list*>(l->cdr);
	EXPECT_EQ(l->car->atype, SYMBOL);
	EXPECT_EQ(l->cdr->atype, LIST);
	l = static_cast<list*>(l->cdr);
	EXPECT_EQ(l->car->atype, FIXNUM);
	EXPECT_EQ(l->cdr->atype, LIST);
	t = t->eval(); // returns 'ok, but we don't actually care

	it = a.env.symbol_table.find("a");
	EXPECT_NE(a.env.symbol_table.end(), it);
	EXPECT_EQ(it->second->atype, FIXNUM);
	i = static_cast<fixnum*>(it->second);
	EXPECT_EQ(i->value, 0);
}

TEST_F(env_test, define_rewrite_is_ok)
{
	std::string s =  "(define a 0)";
	std::string s2 = "(define a 2)";
	fixnum* i;

	t = a.read(s);
	t = t->eval(); // returns 'ok, but we don't actually care
	t = a.read(s2);
	t = t->eval();

	it = a.env.symbol_table.find("a");
	EXPECT_NE(a.env.symbol_table.end(), it);
	EXPECT_EQ(it->second->atype, FIXNUM);
	i = static_cast<fixnum*>(it->second);
	EXPECT_EQ(2, i->value);
}

#if 0 // TODO
TEST_F(env_test, setbang_success)
{
	std::string s =   "(define a 0)";
	std::string s2 =  "(set! a 1)";
TEST_F(env_test, setbang_failure)
{
	std::string s =  "(set! a 0)";
TEST_F(if_test, 2part_ift)
{
	std::string s =  "(if #t 1 2)";
TEST_F(if_test, 2part_iff)
{
	std::string s =  "(if #f 1 2)";
TEST_F(if_test, 1part_ift)
{
	std::string s =  "(if #t 1)";
TEST_F(if_test, 1part_iff)
{
	std::string s =  "(if #f 1)"; => #f
TEST_F(if_test, anything _is_true)
{
	std::string s =  "(if 0 1 2)"; => 1
#endif
