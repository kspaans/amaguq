#include <sstream>
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

	s << "(" << car->print() << " " << cdr->print() << ")";

	return s.str();
}

atom* list::eval()
{
	return this;
}
