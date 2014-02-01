#ifndef __EVAL_H__
#define __EVAL_H__

#include "amaguq.h"

atom* eval_quote(atom* a);
atom* eval_symbol(list* a);

#endif
