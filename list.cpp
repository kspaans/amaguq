#include <iostream>
#include "amaguq.h"

list::list(atom* t)
{
	car = t;
	cdr = nullptr;
}

list::~list()
{
}

std::ostream& operator<<(std::ostream& stream, const list* a)
{
	stream << "()";

	return stream;
}
