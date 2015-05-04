#include <iostream>
#include <string>
#include <exception>
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
		if (std::cin.eof()) {
			std::cout << std::endl;
			break;
		}
		try {
			at = a.read(line);
      at->accept(&a);
			print(at->eval());
		} catch (std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			continue;
		}
		// LOOP!
	}

	std::cout << "Allocations: " << a.hp.allocs << std::endl;
	std::vector<atom*>::iterator it;

	for (it = a.hp.h.begin(); it != a.hp.h.end(); ++it) {
		if (nullptr != *it) {
			std::cout << *it << " " <<
				(*it)->atype << std::endl;
			// TODO print more complete info: stringify the type, value, etc
		} else {
			std::cout << "Oops a NULL in the heap!" << std::endl;
		}
	}

	return 0;
}
