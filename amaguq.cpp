#include <iostream>
#include <string>
#include "amaguq.h"

heap::heap()
{
	allocs = 0;
}

heap::~heap()
{
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

atom::~atom()
{
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

strlit::strlit(const std::string& s)
{
	str = s;
}

strlit::~strlit()
{
}

std::ostream& operator<<(std::ostream& stream, const strlit* a)
{
	stream << a->str;

	return stream;
}

list::list(atom* t)
{
	a = t;
}

list::~list()
{
}

std::ostream& operator<<(std::ostream& stream, const list* a)
{
	stream << "()";

	return stream;
}

amaguq::amaguq()
{
	atom *a;

	a = new boolean("#t");
	hp.alloc(a);
	a = new boolean("#f");
	hp.alloc(a);
	a = new list(nullptr); // "empty list"
	hp.alloc(a);
}

amaguq::~amaguq()
{
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

atom* str_helper(const std::string& s)
{
	std::string::const_iterator it;
	strlit* str;
	unsigned sstate = 0x0;

	for (it = s.begin(); it != s.end(); ++it) {
		if (0x0 == sstate) {
			if ('"' == *it) {
				sstate = 0x1;
			}
		} else if (0x1 == sstate) {
			if ('"' == *it) {
				sstate = 0x2;
			} else if ('\\' == *it) {
				sstate = 0x3;
			}
		} else if (0x2 == sstate) {
			sstate = 0x8;
		} else if (0x3 == sstate) {
			if ('"' == *it) {
				sstate = 0x1;
			} else if ('n' == *it) {
				sstate = 0x1;
			}
		}
	}

	if (0x8 == sstate) {
		std::cerr << "Improper string" << std::endl;
		return nullptr;
	}

	str = new strlit(s);

	return str;
}

atom* list_helper(const std::string& s)
{
	return nullptr;
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
	} else if (0 == s.find('"')) {
		a = str_helper(s);
	} else if (0 == s.find('(')) {
		if (1 == s.find(')')) {
			return hp.h[2];
		} else {
			a = list_helper(s);
		}
	} else {
		a = new fixnum(s);
	}

	hp.alloc(a);

	return a;
}
