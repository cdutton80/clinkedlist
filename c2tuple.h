#ifndef __C2TUPLE_H
#define __C2TUPLE_H
#include "cslinkedlist.h"

typedef struct c2tuple_s {
	const void * fst;
	const void * snd;
} C2Tuple;

#endif