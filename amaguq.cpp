#include <iostream>
#include <string>
#include "amaguq.h"

heap::heap()
{
	std::cout << "Heap contructor!" << std::endl;

	allocs = 0;
}

heap::~heap()
{
	std::cout << "Heap destructor!" << std::endl;
	std::cout << "Allocs: " << allocs << std::endl;

	std::vector<atom*>::iterator it;

	for (it = h.begin(); it != h.end(); ++it) {
		delete *it;
	}
}

void heap::alloc(atom* a)
{
	h.push_back(a);
	allocs += 1;
}

#if 0
atom::atom()
{
	std::cout << "Atom constructor!" << std::endl;
}
#endif

atom::~atom()
{
	std::cout << "Atom destructor!" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const atom* a)
{
	(void)a;
	stream << "()";

	return stream;
}

fixnum::fixnum(const std::string& s)
{
	value = std::stoi(s);
}

fixnum::~fixnum()
{
}

std::ostream& operator<<(std::ostream& stream, const fixnum* a)
{
	stream << a->value;

	return stream;
}

boolean::boolean(const std::string& s)
{
	str = s;
}

boolean::~boolean()
{
}

std::ostream& operator<<(std::ostream& stream, const boolean* a)
{
	stream << a->str;

	return stream;
}

charlit::charlit(const std::string& s)
{
	str = s;
}

charlit::~charlit()
{
}

std::ostream& operator<<(std::ostream& stream, const charlit* a)
{
	stream << a->str;

	return stream;
}

amaguq::amaguq()
{
	std::cout << "Amaguq constructor!" << std::endl;

	atom *a;

	a = new boolean("#t");
	hp.alloc(a);
	a = new boolean("#f");
	hp.alloc(a);
}

amaguq::~amaguq()
{
	std::cout << "Amaguq destructor!" << std::endl;
}

atom* char_helper(const std::string& s)
{
	charlit *c;

	if (2 == s.find(' ')) {
		c = new charlit("#\\space");
	} else if (2 == s.find('\n')) {
		c = new charlit("#\\newline");
	} else {
		c = new charlit(s);
	}

	return c;
}

atom* amaguq::eval(const std::string& s)
{
	atom *a = nullptr;

	if (0 == s.find('#')) {
		if (1 == s.find('t')) {
			return hp.h[0];
		} else if (1 == s.find('f')) {
			return hp.h[1];
		} else if (1 == s.find('\\')) {
			a = char_helper(s);
		}
	} else {
		a = new fixnum(s);
	}

	hp.alloc(a);

	return a;
}
