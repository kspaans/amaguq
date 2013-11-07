#include <iostream>
#include <string>
#include "amaguq.h"

charlit::charlit(const std::string& s)
{
	str = s;
}

charlit::~charlit()
{
}

std::ostream& operator<<(std::ostream& stream, const charlit* a)
{
	stream << a->str;

	return stream;
}
