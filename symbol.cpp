#include "amaguq.h"

symbol::symbol(const std::string& a)
{
	atype = SYMBOL;
	sym = a;
}

symbol::~symbol()
{
}

std::string symbol::print()
{
	return sym;
}

atom* symbol::eval()
{
	// TODO symbols aren't self-evaluating
	return this;
}
