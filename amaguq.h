#ifndef __AMAGUQ_H__
#define __AMAGUQ_H__

#include <string>

struct heap {
	heap();
	~heap();
};

struct atom {
	// Add a polymorphic constructor?
	virtual void eval(void);
};

struct fixnum : atom {
	fixnum(std::string);

	int value;
};

/*
 * Encompases everything needed to lex, parse, and Evaluate code. Reading,
 * Printing, and Looping are done elsewhere.
 */
struct amaguq {
	amaguq();
	~amaguq();

	atom * eval(std::string line);

	heap hp;
};

#endif
