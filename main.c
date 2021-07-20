#include <stdlib.h>
#include <stdio.h>
#include "cslinkedlist.h"
#include "cslinkedlist_utils.h"
#include "c2tuple.h"

void print_int(CPointer val);
void printi_int(CPointer val, int index);
int gt_two(CPointer val);
int lt_ten(CPointer val);
CPointer times_two_plus_one(CPointer val);
void print_intint_tuple(CPointer val);
void print_intflt_tuple(CPointer val);
CPointer int_add(CPointer init, CPointer x);
CPointer times2_plus1_div2(CPointer val);
void printi_2int(CPointer v1, CPointer v2, int i);


int main(void) {
    // int zero = 0;
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    CSList * lst = CSList_alloc(sizeof(int));
    CSList * lst2 = CSList_alloc(sizeof(int));

    for (int i = 0; i < 4; i++) {
        CSList_append_ref(lst, &arr[i]);
    }

    for (int i = 4; i < 8; i++) {
        CSList_append_ref(lst2, &arr[i]);
    }
    
    CSList * lst3 = CSList_intersperse2_ref(lst2, lst);
    
    // CSList_iter(lst3, print_int);
    
    // CSList_iter2i(lst, lst2, printi_2int);
    
    CSList * m = CSList_find_first_n_ref(lst3, 4, gt_two);
    
    CSList_rev_iter(m, print_intint_tuple);
    
    // CSList_iter_where(lst3, print_int, gt_two);
    
    C2Tuple * f = CSList_find_first_ref(lst3, gt_two);
    print_intint_tuple(f);
}

void print_int(CPointer val) {
    fprintf(stdout, "%d\n", *(int *)val);
}

void printi_int(CPointer val, int index) {
    fprintf(stdout, "%3d: %d\n", index + 1, *(int *)val);
}

int gt_two(CPointer val) {
	return *(int *)val > 2;
}

int lt_ten(CPointer val) {
	return *(int *)val < 10;
}

CPointer times_two_plus_one(CPointer val) {
	int * result = malloc(sizeof(int));
	*result = *(int *)val * 2 + 1;
	return result;
}

void print_intint_tuple(CPointer val) {
	C2Tuple * t = (C2Tuple *)val;
	fprintf(stdout, "(%d, %d)\n", *(int *)t->fst, *(int *)t->snd);
}

void print_intflt_tuple(CPointer val) {
    C2Tuple * t = (C2Tuple *)val;
	fprintf(stdout, "(%d, %.2f)\n", *(int *)t->fst, *(float *)t->snd);
}


CPointer int_add(CPointer init, CPointer x) {
    int * result = malloc(sizeof(int));
    *result = *(int *)init + *(int *)x;
    return result;
}

CPointer times2_plus1_div2(CPointer val) {
    float * result = malloc(sizeof(float));
    *result = (float)(*(int *)val * 2 + 1) / 2.0;
    return result;
}

void printi_2int(CPointer v1, CPointer v2, int i) {
	fprintf(stdout, "%3d: %d, %d\n", i, *(int *)v1, *(int *)v2);
}
