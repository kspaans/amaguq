#include <iostream>
#include <string>
#include "amaguq.h"

strlit::strlit(const std::string& s)
{
	str = s;
}

strlit::~strlit()
{
}

std::ostream& operator<<(std::ostream& stream, const strlit* a)
{
	stream << a->str;

	return stream;
}
