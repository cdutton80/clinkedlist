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


int main(void) {
    int zero = 0;
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    CSList * lst = CSList_alloc(sizeof(int));

    for (int i = 0; i < 8; i++) {
        CSList_append_ref(lst, &arr[i]);
    }

	CSList * map = CSList_map_ref(lst, sizeof(int), times_two_plus_one);
    CSList * zip = CSList_zip2_ref(lst, map);
    CSList * cpy = CSList_copy_nodes_and_values(lst);

    CSList * map2 = CSList_map_ref(lst, sizeof(float), times2_plus1_div2);
    CSList * zip2 = CSList_zip2_ref(lst, map2);

    int ** arr2 = (int **)CSList_to_array_of_pointers(CSList_reverse_ref(lst));
    for (int i = 0; i < 8; i++) {
        fprintf(stdout, "arr2[%d] = %d\n", i, *arr2[i]);
    }
    
    fprintf(stdout, "len: %d\n", CSList_length(lst));
    
    CSList_iter(zip, print_intint_tuple);
    CSList_iter(zip2, print_intflt_tuple);

    fprintf(stdout, "sum = %d\n", *(int *)CSList_reduce_ref(cpy, &zero, sizeof(int), int_add));
    
    // C2Tuple * t = zip->head->value;
    
    CSList_free_nodes_and_values(zip);
    free(zip);
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
