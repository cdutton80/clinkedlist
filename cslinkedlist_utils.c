#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cslinkedlist.h"
#include "cslinkedlist_utils.h"

int CSLU_int_cmp(CPointer v1, CPointer v2) {
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;

    return i1 == i2 ? 0 :
           i1 >  i2 ? 1 : -1;
}

int CSLU_int_eq(CPointer v1, CPointer v2) {
    return CSLU_int_cmp(v1, v2) == 0;
}

int CSLU_int_lt(CPointer v1, CPointer v2) {
    return CSLU_int_cmp(v1, v2) == -1;
}

int CSLU_int_gt(CPointer v1, CPointer v2) {
    return CSLU_int_cmp(v1, v2) == 1;
}

int CSLU_int_le(CPointer v1, CPointer v2) {
    return CSLU_int_cmp(v1, v2) <= 0;
}

int CSLU_int_ge(CPointer v1, CPointer v2) {
    return CSLU_int_cmp(v1, v2) >= 0;
}

int CSLU_int_even(CPointer val) {
    return *(int *)val % 2 == 0;
}

int CSLU_int_odd(CPointer val) {
    return *(int *)val % 2 == 1;
}

int CSLU_int_pos(CPointer val) {
    return *(int *)val >= 0;
}

int CSLU_int_neg(CPointer val) {
    return *(int *)val < 0;
}

CPointer CSLU_int_add(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = *(int *)v1 + *(int *)v2;
    return result;
}

CPointer CSLU_int_sub(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = *(int *)v1 - *(int *)v2;
    return result;
}

CPointer CSLU_int_mul(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = *(int *)v1 * *(int *)v2;
    return result;
}

CPointer CSLU_int_div(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = *(int *)v1 / *(int *)v2;
    return result;
}

CPointer CSLU_int_pow(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = pow((double)(*(int *)v1), (double)(*(int *)v2));
    return result;
}

CPointer CSLU_int_mod(CPointer v1, CPointer v2) {
    int * result = malloc(sizeof(int));
    *result = *(int *)v1 % *(int *)v2;
    return result;
}

CPointer CSLU_int_to_flt(CPointer v1) {
    float * result = malloc(sizeof(float));
    *result = (float)(*(int *)v1);
    return result;
}

void CSLU_int_println(CPointer val) {
    printf("%d\n", *(int *)val);
}

void CSLU_int_println_idx(CPointer val, int index) {
    printf("%d: %d\n", index, *(int *)val);
}

CPointer CSLU_int_negate(CPointer val) {
    int * result = malloc(sizeof(int));
    *result = -(*(int *)val);
    return result;
}

// int CSLU_flt_cmp(CPointer v1, CPointer v2);
// int CSLU_flt_eq(CPointer v1, CPointer v2);
// int CSLU_flt_lt(CPointer v1, CPointer v2);
// int CSLU_flt_gt(CPointer v1, CPointer v2);
// int CSLU_flt_le(CPointer v1, CPointer v2);
// int CSLU_flt_ge(CPointer v1, CPointer v2);
// int CSLU_int_pos(CPointer val);
// int CSLU_int_neg(CPointer val);
// CPointer CSLU_flt_add(CPointer v1, CPointer v2);
// CPointer CSLU_flt_sub(CPointer v1, CPointer v2);
// CPointer CSLU_flt_mul(CPointer v1, CPointer v2);
// CPointer CSLU_flt_div(CPointer v1, CPointer v2);
// CPointer CSLU_flt_pow(CPointer v1, CPointer v2);
// CPointer CSLU_flt_to_int(CPointer v1);
// void CSLU_flt_println(CPointer val);
// void CSLU_flt_println_idx(CPointer val, int index);
// CPointer CSLU_flt_negate(CPointer val);

// void print_int_int_tuple(C2Tuple * t);
// void print_int_flt_tuple(C2Tuple * t);
// void print_flt_flt_tuple(C2Tuple * t);
// void print_flt_int_tuple(C2Tuple * t);
// void print_int_intlist_tuple(C2Tuple * t);
// void print_int_fltlist_tuple(C2Tuple * t);
