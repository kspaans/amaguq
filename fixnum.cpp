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

atom* fixnum::accept(amaguq* visitor)
{
	return visitor->visit(this);
}
