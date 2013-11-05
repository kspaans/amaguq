#ifndef __AMAGUQ_H__
#define __AMAGUQ_H__

#include <ostream>
#include <string>
#include <vector>

struct atom {
	virtual ~atom();

	friend std::ostream& operator<<(std::ostream& stream, const atom* a);
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

	heap hp;
};

#endif
