#include <vector>
#include "amaguq.h"

heap::heap()
{
	allocs = 0;
}

heap::~heap()
{
	std::vector<atom*>::iterator it;

	for (it = h.begin(); it != h.end(); ++it) {
		delete *it;
	}
}

void heap::alloc(atom* a)
{
	h.push_back(a);
	allocs += 1;
}
