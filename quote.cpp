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

atom* quote::accept(amaguq* visitor)
{
	return visitor->visit(this);
}
