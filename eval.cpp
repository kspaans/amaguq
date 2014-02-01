#include <string>
#include <stdexcept>
#include "amaguq.h"
#include "eval.h"
#include <iostream>

const std::string KEYWORD_QUOTE("quote");

atom* eval_quote(atom* a)
{
	if (SYMBOL == a->atype) {
		return a;
	} else {
		throw std::logic_error("Cannot quote this type");
	}

	return a;
}

atom* eval_symbol(list* l)
{
	symbol* s = static_cast<symbol*>(l->car);

	if (s->sym == KEYWORD_QUOTE) {
		std::cout << "quoting eval: " << std::endl;
		// TODO destroy the parent list?
		return eval_quote(l->cdr);
	} else {
		std::cout << "unknown symbol!!!!!" << std::endl;
	}

	return s;
}

/*
 * Temporary name of an eval function that takes symols and returns symbols
 * performing syntactic and semantic evaluation.
 */
atom* actual_eval();
