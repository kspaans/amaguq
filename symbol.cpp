#include <iostream>
#include <string>
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
	return "";
}

atom* symbol::eval()
{
	return this;
}
