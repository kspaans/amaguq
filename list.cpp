#include <sstream>
#include <stdexcept>
#include "amaguq.h"

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

	if (nullptr == car && nullptr == cdr) {
		// TODO make empty list be a subclass of the list class
		s << "()";
	} else {
		s << "(" << car->print() << " " << cdr->print() << ")";
	}

	return s.str();
}

atom* list::eval()
{
	if (nullptr == car && nullptr == cdr) {
		throw std::logic_error("Cannot evaluate empty list");
	}
	if (SYMBOL == car->atype) {
		return car->accept(new list_visitor(this));
	} else {
		throw std::logic_error("Cannot evaluate list");
	}
}

atom* list::accept(amaguq* visitor)
{
	return visitor->visit(this);
}
