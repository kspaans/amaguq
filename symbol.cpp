#include <stdexcept>
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
	// TODO look up the symbol in the environment
	throw std::logic_error("Symbol not found in environment");
}
