#include <iostream>
#include <string>
#include "amaguq.h"










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
