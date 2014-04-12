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

	env.parent = nullptr;
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
		std::string blah(s.c_str() + idx, s.c_str() + s.length());
		c = new charlit(blah);
	}
	idx += 3;

	return c;
}

atom* str_helper(const std::string& s, unsigned& idx)
{
	strlit* str;
	unsigned sstate = 0x0;
	unsigned length = s.length();
	unsigned init = idx;

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

	str = new strlit(s.c_str() + init);

	return str;
}

void gobble_whitespace(const std::string& s, unsigned& idx)
{
	while (s[idx] == ' ' || s[idx] == '\t') {
		idx += 1;
	}
}

atom* amaguq::read_pair(const std::string& s, unsigned& idx)
{
	list* l;
	atom* car;
	atom* cdr;

	if (s[idx] == ')') {
		++idx;
		return hp.h[2]; // empty list
	}
	car = reads(s, idx);
	gobble_whitespace(s, idx);

	if (s[idx] == '.') {
		++idx;
		cdr = reads(s, idx);
		gobble_whitespace(s, idx);
		if (s[idx] != ')') {
		// expect ')' else throw excptn TODO
		}
		++idx;
	} else {
		cdr = read_pair(s, idx);
	}

	l = new list(car, cdr);
	hp.alloc(l);

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

	// TODO symbols can be more than alphanumerics
	while (isalnum(s[idx]) && idx <= length) {
		idx += 1;
	}

	std::string blah(s.c_str() + init, s.c_str() + idx);

	return new symbol(blah);
}

atom* amaguq::reads(const std::string& s, unsigned& idx)
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
		a = read_pair(s, ++idx);
	} else if ((s[idx] >= 'a' && s[idx] <= 'z')
			|| (s[idx] >= 'A' && s[idx] <= 'Z')) {
		a = symbol_helper(s, idx);
		hp.alloc(a);
	} else if (('\'' == s[idx])) {
		a = reads(s, ++idx);
		// TODO should the intermediate stuff be added to the heap?
		a = new quote(a);
		hp.alloc(a);
	} else {
		a = fixnum_helper(s, idx);
		hp.alloc(a);
	}

	return a;
}

atom* amaguq::read(const std::string& s)
{
	unsigned idx = 0;
	atom* a;

	a = reads(s, idx);
	a->interpreter = this;
	return a;
}
