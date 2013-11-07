#include <iostream>
#include "amaguq.h"

atom::~atom()
{
}

std::ostream& operator<<(std::ostream& stream, const atom* a)
{
	(void)a;
	stream << "()";

	return stream;
}
