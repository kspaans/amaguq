#include <sstream>
#include <stdexcept>
#include "amaguq.h"
#include "eval.h"

list::list(atom* t, atom *tt)
{
	car = t;
	cdr = tt;
	atype = LIST;
}

list::~list()
{
}

std::string list::print()
{
	std::stringstream s;

	s << "(" << car->print() << " " << cdr->print() << ")";

	return s.str();
}

atom* list::eval()
{
	if (nullptr == car && nullptr == cdr) {
		throw std::logic_error("Cannot evaluate empty list");
	}
	if (SYMBOL == car->atype) {
		return eval_symbol(this);
	} else {
		throw std::logic_error("Cannot evaluate list");
	}
}
