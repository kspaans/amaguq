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
	table::iterator it;

	it = interpreter->env.symbol_table.find(sym);
	if (interpreter->env.symbol_table.end() == it ) {
		throw std::logic_error("Symbol not found in environment");
	}

	return it->second;
}
