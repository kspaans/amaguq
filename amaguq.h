#ifndef __AMAGUQ_H__
#define __AMAGUQ_H__

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include "types.h"

typedef std::map<std::string, atom*> table;

struct environment {
	environment* parent;
	table symbol_table;
};

struct heap {
	heap();
	~heap();

	void alloc(atom*);

	std::vector<atom*> h;
	int allocs;
};

/*
 * Encompases everything needed to lex, parse, and Evaluate code. Reading,
 * Printing, and Looping are done elsewhere.
 */
struct amaguq {
	amaguq();
	~amaguq();

	// TODO change this to 'read' or similar
	atom* eval(const std::string&);
	atom* read(const std::string&, unsigned&);
	atom* eval_pair(const std::string&, unsigned&);

	heap hp;
	environment env;
};

#endif
