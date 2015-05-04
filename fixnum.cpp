#include <sstream>
#include "amaguq.h"

fixnum::fixnum(const std::string& s)
{
	atype = FIXNUM;
	value = std::stoi(s);
}

fixnum::~fixnum()
{
}

std::string fixnum::print()
{
	std::stringstream s;

	s << value;
	return s.str();
}

atom* fixnum::eval()
{
	return this;
}

void fixnum::accept(amaguq* visitor)
{
	visitor->visit(this);
}
