#include <iostream>
#include <string>
#include "amaguq.h"

heap::heap()
{
	std::cout << "Heap contructor!" << std::endl;
}

heap::~heap()
{
	std::cout << "Heap destructor!" << std::endl;
}

void atom::eval()
{
	return;
}

#if 0
atom::atom()
{
	std::cout << "Atom constructor!" << std::endl;
}

atom::~atom()
{
	std::cout << "Atom destructor!" << std::endl;
}
#endif

fixnum::fixnum(std::string s)
{
	value = std::stoi(s);
}

amaguq::amaguq()
{
	std::cout << "Amaguq constructor!" << std::endl;
}

amaguq::~amaguq()
{
	std::cout << "Amaguq destructor!" << std::endl;
}

atom * amaguq::eval(std::string s)
{
	fixnum *a = new fixnum(s);

	return a;
}
