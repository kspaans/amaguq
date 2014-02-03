#ifndef __AMAGUQ_H__
#define __AMAGUQ_H__

#include <ostream>
#include <string>
#include <vector>
#include "types.h"

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
