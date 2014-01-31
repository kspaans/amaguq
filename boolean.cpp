#include "amaguq.h"

boolean::boolean(const std::string& s)
{
	str = s;
	atype = BOOLEAN;
}

boolean::~boolean()
{
}

std::string boolean::print()
{
	return str;
}

atom* boolean::eval()
{
	return this;
}
