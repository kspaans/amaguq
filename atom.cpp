#include <sstream>
#include "amaguq.h"

atom::~atom()
{
	atype = ATOM;
}

std::string atom::print()
{
	std::stringstream s;

	s << "{atom:" << this << "}";
	return s.str();
}

/*
 * We should never get a bare atom, so this may be a bug?
 */
atom* atom::eval()
{
	return this;
}
