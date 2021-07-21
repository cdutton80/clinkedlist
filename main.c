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
int cmp_int(CPointer v1, CPointer v2);
CPointer int_mod4(CPointer val);

void print_intlist(CSList * list);
void print_int_intlist_tuple(C2Tuple * t);


int main(void) {
    int zero = 0;
    int one = 1;
    int two = 2;
    int eight = 8;
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

    CSList_append_ref(lst3, &one);
    CSList_append_ref(lst3, &two);
    CSList_append_ref(lst3, &eight);




    CSList * u = CSList_uniq_ref(lst3, cmp_int);


    CSList * z = CSList_group_by_ref(lst3, sizeof(int), int_mod4, cmp_int);
    
    CSList_iter(z, print_int_intlist_tuple);
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

int cmp_int(CPointer v1, CPointer v2) {
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;

    return i1 == i2 ? 0 : 
           i1 > i2  ? 1 : -1;
}


CPointer int_mod4(CPointer val) {
    int * result = malloc(sizeof(int));
    *result = *(int *)val % 4;
    return result;
}

void print_intlist(CSList * list) {
    if (list == NULL) {
        printf("(nil)");
    }
    else if (CSList_empty(list)) {
        printf("[]");
    }
    else if (CSList_cmp_len_with(list, 1) == 0) {
        printf("[%d]\n", *(int *)list->head->value);
    }
    else {
        printf("[");
        CSNode * cur;
        for (cur = list->head; cur->next != NULL; cur = cur->next) {
            printf("%d, ", *(int *)cur->value);
        }

        printf("%d]\n", *(int *)cur->value);
    }
}

void print_int_intlist_tuple(C2Tuple * t) {
    int i = *(int *)t->fst;
    CSList * il = (CSList *)t->snd;

    printf("(%d, ", i);
    print_intlist(il);
    printf(")\n");
}
