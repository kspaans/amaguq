#include <string>
#include <sstream>
#include <stdexcept>
#include "amaguq.h"

#include <iostream>
const std::string KEYWORD_QUOTE("quote");
const std::string KEYWORD_DEFINE("define");
const std::string KEYWORD_SETBANG("set!");
const std::string KEYWORD_IF("if");

atom* amaguq::eval_quote(atom* a)
{
	if (SYMBOL == a->atype) {
		return a;
	} else if (FIXNUM == a->atype) {
		return a;
	} else if (BOOLEAN == a->atype) {
		return a;
	} else if (CHARLIT == a->atype) {
		return a;
	} else if (STRLIT == a->atype) {
		return a;
	} else {
		throw std::logic_error("Cannot quote this type");
	}

	return a;
}

symbol* amaguq::eval_define(atom* a)
{
	list* l;
	list* expr;
	symbol* s;
	std::pair<table::iterator, bool> inserted_pair;

	if (LIST == a->atype) {
		l = static_cast<list*>(a);
	} else {
		throw std::logic_error("define with no list");
	}
	if (LIST == l->cdr->atype) {
		expr = static_cast<list*>(l->cdr);
		if (SYMBOL != expr->car->atype) {
			throw std::logic_error("define with no symbol");
		}
	} else {
		throw std::logic_error("improper argument to define");
	}
	if (LIST != expr->cdr->atype) {
		throw std::logic_error("improper expression in define");
	}
	s = static_cast<symbol*>(expr->car);
	expr = static_cast<list*>(expr->cdr);
	if (expr->cdr != hp.h[2]) { // empty list
		throw std::logic_error("extra arguments in expression");
	}

	inserted_pair = env.symbol_table.insert(
		std::make_pair(s->sym, expr->car->eval())
	);
	if (!inserted_pair.second) {
		env.symbol_table.erase(env.symbol_table.find(s->sym));
		env.symbol_table.insert(
			std::make_pair(s->sym, expr->car->eval())
		);
	}

	// TODO memory leak
	return new symbol("OK");
}

symbol* amaguq::eval_setbang(list* l)
{
	list* expr;
	symbol* s;
	table::iterator it;

	if (LIST == l->cdr->atype) {
		expr = static_cast<list*>(l->cdr);
		if (SYMBOL != expr->car->atype) {
			throw std::logic_error("set! with no symbol");
		}
	} else {
		throw std::logic_error("improper argument to set!");
	}
	if (LIST != expr->cdr->atype) {
		throw std::logic_error("improper expression in set!");
	}
	s = static_cast<symbol*>(expr->car);
	expr = static_cast<list*>(expr->cdr);
	if (expr->cdr != hp.h[2]) { // empty list
		throw std::logic_error("extra arguments in expression");
	}

	it = env.symbol_table.find(s->sym);
	if (env.symbol_table.end() == it) {
		throw std::logic_error("symbol not defined");
	} else {
		env.symbol_table.erase(it);
		env.symbol_table.insert(
			std::make_pair(s->sym, expr->car->eval())
		);
	}

	return new symbol("OK");
}

atom* amaguq::eval_if(list* l)
{
	if (LIST == l->cdr->atype) {
		return l->cdr->accept(new if_visitor(static_cast<list*>(l->cdr)));
	} else {
		throw std::logic_error("Malformed IF statement");
	}
}

atom* amaguq::eval_if_body(list* l, boolean* b) {
  // FIXME why isn't this boolean a singleton? Is it a copy-constructor?
  if (b->str == "#t") { //(b == hp.h[0]) {
    return l->cdr->accept(new if_true_visitor(static_cast<list*>(l->cdr)));
  } else if (l->cdr == hp.h[2]) { // empty list
    return hp.h[1];
  } else {
    return l->cdr->accept(new if_false_visitor(static_cast<list*>(l->cdr)));
  }
}

atom* amaguq::eval_symbol_list(list* l, symbol *s)
{
	if (s->sym == KEYWORD_QUOTE) {
		// TODO destroy the parent list?
		return eval_quote(l->cdr);
	} else if (s->sym == KEYWORD_DEFINE) {
		return eval_define(l);
	} else if (s->sym == KEYWORD_SETBANG) {
		return eval_setbang(l);
	} else if (s->sym == KEYWORD_IF) {
		return eval_if(l);
	} else {
		std::stringstream err;
		err << "Unknown symbol: " << s->sym;
		throw std::logic_error(err.str());
	}

	return s;
}

atom* amaguq::visit(fixnum* fixnum)
{
	return fixnum->eval();
}

atom* amaguq::visit(boolean* boolean)
{
	return boolean->eval();
}

atom* amaguq::visit(charlit* charlit)
{
	return charlit->eval();
}

atom* amaguq::visit(strlit* strlit)
{
	return strlit->eval();
}

atom* amaguq::visit(list* list)
{
	return list->eval();
}

atom* amaguq::visit(symbol* symbol)
{
	return symbol->eval();
}

atom* amaguq::visit(quote* quote)
{
	return quote->eval();
}

// // // //  // // // //

list_visitor::list_visitor(list* l)
{
	body = l;
}

list_visitor::~list_visitor()
{
}

atom* list_visitor::visit(symbol* s)
{
	return amaguq::eval_symbol_list(body, s);
}

// // // //  // // // //

if_visitor::if_visitor(list* l)
{
	body = l;
}

if_visitor::~if_visitor()
{
}

atom* if_visitor::visit(list* l)
{
	return amaguq::eval_if_body(body, dynamic_cast<boolean*>(l->car));
}

// // // //  // // // //

if_true_visitor::if_true_visitor(list* l)
{
	body = l;
}

if_true_visitor::~if_true_visitor()
{
}

atom* if_true_visitor::visit(list* l)
{
  return l->car->eval();
}

// // // //  // // // //

if_false_visitor::if_false_visitor(list* l)
{
	body = l;
}

if_false_visitor::~if_false_visitor()
{
}

atom* if_false_visitor::visit(list* l)
{
  // The result is whatever l->cdr->car evaluates to, so we can reuse the
  // if_true_visitor functionality.
  return l->cdr->accept(new if_true_visitor(static_cast<list*>(l->cdr)));
}
