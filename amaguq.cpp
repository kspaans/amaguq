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
	a = new list(nullptr, nullptr); // "empty list"
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

atom* str_helper(const std::string& s, unsigned& idx)
{
	strlit* str;
	unsigned sstate = 0x0;
	unsigned length = s.length();

	for (; idx != length; ++idx) {
		if (0x0 == sstate) {
			if ('"' == s[idx]) {
				sstate = 0x1;
			}
		} else if (0x1 == sstate) {
			if ('"' == s[idx]) {
				sstate = 0x2;
			} else if ('\\' == s[idx]) {
				sstate = 0x3;
			}
		} else if (0x2 == sstate) {
			sstate = 0x8;
		} else if (0x3 == sstate) {
			if ('"' == s[idx]) {
				sstate = 0x1;
			} else if ('n' == s[idx]) {
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

atom* amaguq::eval_pair(const std::string& s, unsigned& idx)
{
	list* l;
	atom* car;
	atom* cdr;

	car = read(s, idx);
	cdr = read(s, idx);
	
	l = new list(car, cdr);

	return l;
}

atom* split_on_space(const std::string& s)
{
	unsigned idx = 0;

	while (s[idx] != ' ') {
		idx += 1;
	}

	return new fixnum(std::string(s.c_str(), s.c_str() + idx));
}

atom* amaguq::read(const std::string& s, unsigned& idx)
{
	atom *a = nullptr;

	if ('#' == s[idx]) {
		if ('t' == s[idx + 1]) {
			return hp.h[0];
		} else if ('f' == s[idx + 1]) {
			return hp.h[1];
		} else if ('\\' == s[idx + 1]) {
			a = char_helper(s);
		}
	} else if ('"' == s[idx]) {
		a = str_helper(s, idx);
	} else if ('(' == s[idx]) {
		if (')' == s[idx + 1]) {
			return hp.h[2]; // empty list
		} else {
			a = eval_pair(s.substr(1), ++idx);
		}
	} else {
		a = split_on_space(s); //new fixnum(s);
		std::cout << "Got fixnum \'" << reinterpret_cast<fixnum*>(a) << "\'" << std::endl;
	}

	hp.alloc(a);

	return a;
}

atom* amaguq::eval(const std::string& s)
{
	unsigned idx = 0;

	return read(s, idx);
}
