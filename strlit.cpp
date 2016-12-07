#include "amaguq.h"

strlit::strlit(const std::string& s)
{
	str = s;
}

strlit::~strlit()
{
}

std::string strlit::print()
{
	return str;
}

atom* strlit::eval()
{
	return this;
}

atom* strlit::accept(amaguq* visitor)
{
	visitor->visit(this);
}
