#include <iostream>
#include <string>
#include "amaguq.h"

boolean::boolean(const std::string& s)
{
	str = s;
}

boolean::~boolean()
{
}

std::ostream& operator<<(std::ostream& stream, const boolean* a)
{
	stream << a->str;

	return stream;
}