#include <string>
#include <sstream>
#include <stdexcept>
#include "amaguq.h"
#include "eval.h"

const std::string KEYWORD_QUOTE("quote");

atom* eval_quote(atom* a)
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

atom* eval_symbol(list* l)
{
	symbol* s = static_cast<symbol*>(l->car);

	if (s->sym == KEYWORD_QUOTE) {
		// TODO destroy the parent list?
		return eval_quote(l->cdr);
	} else {
		std::stringstream err;
		err << "Unknown symbol: " << s->sym;
		throw std::logic_error(err.str());
	}

	return s;
}

/*
 * Temporary name of an eval function that takes symols and returns symbols
 * performing syntactic and semantic evaluation.
 */
atom* actual_eval();
