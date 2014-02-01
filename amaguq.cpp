#include <iostream>
#include <string>
#include "amaguq.h"
#include "eval.h"

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

atom* char_helper(const std::string& s, unsigned& idx)
{
	charlit *c;

	if (' ' == s[idx + 2]) {
		c = new charlit("#\\space");
	} else if ('\n' == s[idx + 2]) {
		c = new charlit("#\\newline");
	} else {
		c = new charlit(s);
	}
	idx += 3;

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

atom* fixnum_helper(const std::string& s, unsigned& idx)
{
	const unsigned init = idx;
	const unsigned length = s.length();

	while ((isalnum(s[idx]) || '-' == s[idx]) && idx <= length) {
		idx += 1;
	}

	std::string blah(s.c_str() + init, s.c_str() + idx);

	return new fixnum(blah);
}

symbol* symbol_helper(const std::string& s, unsigned& idx)
{
	const unsigned init = idx;
	const unsigned length = s.length();

	while (isalnum(s[idx]) && idx <= length) {
		idx += 1;
	}

	std::string blah(s.c_str() + init, s.c_str() + idx);

	return new symbol(blah);
}

void gobble_whitespace(const std::string& s, unsigned& idx)
{
	while (s[idx] == ' ' || s[idx] == '\t') {
		idx += 1;
	}
}

atom* amaguq::read(const std::string& s, unsigned& idx)
{
	atom *a = nullptr;

	gobble_whitespace(s, idx);


	if ('#' == s[idx]) {
		if ('t' == s[idx + 1]) {
			a = hp.h[0];
		} else if ('f' == s[idx + 1]) {
			a = hp.h[1];
		} else if ('\\' == s[idx + 1]) {
			a = char_helper(s, idx);
			hp.alloc(a);
		}
	} else if ('"' == s[idx]) {
		a = str_helper(s, idx);
		hp.alloc(a);
	} else if ('(' == s[idx]) {
		if (')' == s[idx + 1]) {
			idx += 2;
			a = hp.h[2]; // empty list
		} else {
			a = eval_pair(s, ++idx);
			hp.alloc(a);
		}
	} else if ('.' == s[idx]) {
		// list special? FIXME
		a = read(s, ++idx);
	} else if ((s[idx] >= 'a' && s[idx] <= 'z')
			|| (s[idx] >= 'A' && s[idx] <= 'Z')) {
		a = symbol_helper(s, idx);
		hp.alloc(a);
	} else if (('\'' == s[idx])) {
		a = read(s, ++idx);
		// TODO should the intermediate stuff be added to the heap?
		a = eval_quote(a);
	} else {
		a = fixnum_helper(s, idx);
		hp.alloc(a);
	}

	return a;
}

atom* amaguq::eval(const std::string& s)
{
	unsigned idx = 0;

	return read(s, idx);
}
