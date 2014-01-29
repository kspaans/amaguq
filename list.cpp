#include <iostream>
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

std::ostream& operator<<(std::ostream& stream, const list* a)
{
	stream << "()";
	// TODO pretty printing of lists
	(void)a;

	return stream;
}
