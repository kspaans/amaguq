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
	std::cout << a->print();
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
