#include <iostream>
#include <string>
#include "amaguq.h"

std::string read(void)
{
	std::string line;

	std::getline(std::cin, line);
	return line;
}

void print(atom *a)
{
	fixnum*  fn;
	boolean* b;
	charlit* c;
	strlit*  s;
	symbol* sy;

	fn = dynamic_cast<fixnum*>(a);
	if (nullptr != fn) {
		std::cout << fn;
		goto done;
	}
	b = dynamic_cast<boolean*>(a);
	if (nullptr != b) {
		std::cout << b;
		goto done;
	}
	c = dynamic_cast<charlit*>(a);
	if (nullptr != c) {
		std::cout << c;
		goto done;
	}
	s = dynamic_cast<strlit*>(a);
	if (nullptr != s) {
		std::cout << s;
		goto done;
	}
	switch (a->atype) {
	case SYMBOL:
		sy = reinterpret_cast<symbol*>(a);
		std::cout << sy;
		goto done;

	default:
		std::cout << "Whoops!" << std::endl;
		goto done;
	}

	std::cout << a;

done:
	std::cout << std::endl;
}

int main(void)
{
	amaguq a;
	atom *at;
	std::string line;

	std::cout << "Bienvenu au Amaguq Scheme interpreter. Press Ctrl-C to exit." << std::endl;

	while (1) {
		std::cout << "> ";
		line = read();
		at = a.eval(line);
		print(at);
		// LOOP!
	}

	return 0;
}
