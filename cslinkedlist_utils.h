#ifndef __CSLINKEDLIST_UTILS_H
#define __CSLINKEDLIST_UTILS_H

#include <stdlib.h>
#include <math.h>
#include "cslinkedlist.h"
#include "c2tuple.h"


int CSLU_int_cmp(CPointer v1, CPointer v2);
int CSLU_int_eq(CPointer v1, CPointer v2);
int CSLU_int_lt(CPointer v1, CPointer v2);
int CSLU_int_gt(CPointer v1, CPointer v2);
int CSLU_int_le(CPointer v1, CPointer v2);
int CSLU_int_ge(CPointer v1, CPointer v2);
int CSLU_int_even(CPointer val);
int CSLU_int_odd(CPointer val);
int CSLU_int_pos(CPointer val);
int CSLU_int_neg(CPointer val);
CPointer CSLU_int_add(CPointer v1, CPointer v2);
CPointer CSLU_int_sub(CPointer v1, CPointer v2);
CPointer CSLU_int_mul(CPointer v1, CPointer v2);
CPointer CSLU_int_div(CPointer v1, CPointer v2);
CPointer CSLU_int_pow(CPointer v1, CPointer v2);
CPointer CSLU_int_mod(CPointer v1, CPointer v2);
CPointer CSLU_int_to_flt(CPointer v1);
void CSLU_int_println(CPointer val);
void CSLU_int_println_idx(CPointer val, int index);

int CSLU_flt_cmp(CPointer v1, CPointer v2);
int CSLU_flt_eq(CPointer v1, CPointer v2);
int CSLU_flt_lt(CPointer v1, CPointer v2);
int CSLU_flt_gt(CPointer v1, CPointer v2);
int CSLU_flt_le(CPointer v1, CPointer v2);
int CSLU_flt_ge(CPointer v1, CPointer v2);
int CSLU_int_pos(CPointer val);
int CSLU_int_neg(CPointer val);
CPointer CSLU_flt_add(CPointer v1, CPointer v2);
CPointer CSLU_flt_sub(CPointer v1, CPointer v2);
CPointer CSLU_flt_mul(CPointer v1, CPointer v2);
CPointer CSLU_flt_div(CPointer v1, CPointer v2);
CPointer CSLU_flt_pow(CPointer v1, CPointer v2);
CPointer CSLU_flt_mod(CPointer v1, CPointer v2);
CPointer CSLU_flt_to_int(CPointer v1);
void CSLU_flt_println(CPointer val);
void CSLU_flt_println_idx(CPointer val, int index);

void print_int_int_tuple(C2Tuple * t);
void print_int_flt_tuple(C2Tuple * t);
void print_flt_flt_tuple(C2Tuple * t);
void print_flt_int_tuple(C2Tuple * t);
void print_int_intlist_tuple(C2Tuple * t);
void print_int_fltlist_tuple(C2Tuple * t);



#endif
