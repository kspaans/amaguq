#include "amaguq.h"

charlit::charlit(const std::string& s)
{
	str = s;
	atype = CHARLIT;
}

charlit::~charlit()
{
}

std::string charlit::print()
{
	return str;
}

atom* charlit::eval()
{
	return this;
}

void charlit::accept(amaguq* visitor)
{
	visitor->visit(this);
}
