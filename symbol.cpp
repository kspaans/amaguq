#include <iostream>
#include <string>
#include "amaguq.h"

symbol::symbol(const std::string& a)
{
	atype = SYMBOL;
	sym = a;
}

symbol::~symbol()
{
}

std::ostream& operator<<(std::ostream& stream, const symbol* a)
{
	stream << a->sym;

	return stream;
}
