#include <string>
#include <sstream>
#include <stdexcept>
#include "amaguq.h"

#include <iostream>
const std::string KEYWORD_QUOTE("quote");
const std::string KEYWORD_DEFINE("define");

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

atom* amaguq::eval_symbol(list* l)
{
	symbol* s = static_cast<symbol*>(l->car);

	if (s->sym == KEYWORD_QUOTE) {
		// TODO destroy the parent list?
		return eval_quote(l->cdr);
	} else if (s->sym == KEYWORD_DEFINE) {
		return eval_define(l);
	} else {
		std::stringstream err;
		err << "Unknown symbol: " << s->sym;
		throw std::logic_error(err.str());
	}

	return s;
}
