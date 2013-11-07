#include <iostream>
#include <string>
#include "amaguq.h"

fixnum::fixnum(const std::string& s)
{
	value = std::stoi(s);
}

fixnum::~fixnum()
{
}

std::ostream& operator<<(std::ostream& stream, const fixnum* a)
{
	stream << a->value;

	return stream;
}
