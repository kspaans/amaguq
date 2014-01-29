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

	friend std::ostream& operator<<(std::ostream& stream, const atom* a);

	a_type atype;
};

struct fixnum : atom {
	fixnum(const std::string&);
	~fixnum();

	friend std::ostream& operator<<(std::ostream& stream, const fixnum* a);

	int value;
};

struct boolean : atom {
	boolean(const std::string&);
	~boolean();

	friend std::ostream& operator<<(std::ostream& stream, const boolean* a);

	std::string str;
};

struct charlit : atom {
	charlit(const std::string&);
	~charlit();

	friend std::ostream& operator<<(std::ostream& stream, const charlit* a);

	std::string str;
};

struct strlit : atom {
	strlit(const std::string&);
	~strlit();

	friend std::ostream& operator<<(std::ostream& stream, const strlit* a);

	std::string str;
};

struct list : atom {
	list(atom*, atom*);
	~list();

	friend std::ostream& operator<<(std::ostream& stream, const list* a);

	atom* car;
	atom* cdr;
};

struct symbol : atom {
	symbol(const std::string&);
	~symbol();

	friend std::ostream& operator<<(std::ostream& stream, const symbol* s);

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

	atom* eval(const std::string&);
	atom* read(const std::string&, unsigned&);
	atom* eval_pair(const std::string&, unsigned&);

	heap hp;
};

#endif
