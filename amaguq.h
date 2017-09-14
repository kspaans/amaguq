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
	atom* eval_symbol_list(list*, symbol*);
	atom* eval_quote(atom*);
	symbol* eval_define(atom*);
	symbol* eval_setbang(list*);
	atom* eval_if(list*);
	atom* eval_if_body(list*, boolean *);
	atom* visit(fixnum*);
	virtual atom* visit(boolean*);
	atom* visit(charlit*);
	atom* visit(strlit*);
	virtual atom* visit(list*);
	virtual atom* visit(symbol*);
	atom* visit(quote*);

	// TODO change member variables to start with _
	heap hp;
	environment env;
};

struct list_visitor : amaguq {
	list_visitor(list*);
	~list_visitor();

	virtual atom* visit(symbol*);

	list* body;
};

struct if_visitor : amaguq {
	if_visitor(list*);
	~if_visitor();

	virtual atom* visit(list*);

	list* body;
};

struct if_true_visitor : amaguq {
	if_true_visitor(list*);
	~if_true_visitor();

	virtual atom* visit(list*);

	list* body;
};

struct if_false_visitor : amaguq {
	if_false_visitor(list*);
	~if_false_visitor();

	virtual atom* visit(list*);

	list* body;
};

#endif
