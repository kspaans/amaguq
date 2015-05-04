#include "amaguq.h"

quote::quote(atom* at)
{
	atype = QUOTE;
	q = at;
}

quote::~quote()
{
}

std::string quote::print()
{
	return q->print();
}

atom* quote::eval()
{
	return q;
}

void quote::accept(amaguq* visitor)
{
	visitor->visit(this);
}
