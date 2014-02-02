#ifndef __AMAGUQ_H__
#define __AMAGUQ_H__

#include <ostream>
#include <string>
#include <vector>

enum a_type {
	ATOM,
	FIXNUM,
	BOOLEAN,
	CHARLIT,
	STRLIT,
	LIST,
	SYMBOL,
};

struct atom {
	virtual ~atom();

	virtual std::string print();
	virtual atom* eval();

	a_type atype;
};

struct fixnum : atom {
	fixnum(const std::string&);
	~fixnum();

	virtual std::string print();
	virtual atom* eval();

	int value;
};

struct boolean : atom {
	boolean(const std::string&);
	~boolean();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct charlit : atom {
	charlit(const std::string&);
	~charlit();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct strlit : atom {
	strlit(const std::string&);
	~strlit();

	virtual std::string print();
	virtual atom* eval();

	std::string str;
};

struct list : atom {
	list(atom*, atom*);
	~list();

	virtual std::string print();
	virtual atom* eval();

	atom* car;
	atom* cdr;
};

struct symbol : atom {
	symbol(const std::string&);
	~symbol();

	virtual std::string print();
	virtual atom* eval();

	std::string sym;
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
};

#endif
