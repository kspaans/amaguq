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

	atom* read(const std::string&);
	atom* reads(const std::string&, unsigned&);
	atom* read_pair(const std::string&, unsigned&);
	atom* eval_symbol(list* a);
	atom* eval_quote(atom* a);
	symbol* eval_define(atom* a);

	// TODO change member variables to start with _
	heap hp;
	environment env;
};

#endif
