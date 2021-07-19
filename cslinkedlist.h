#ifndef __CSLINKEDLIST_H
#define __CSLINKEDLIST_H

#include <stdlib.h>
#include "c2tuple.h"

// const size_t INT_SIZE = sizeof(int);

typedef const void * CConstPointer;
typedef void * CPointer; 

typedef struct node_s {
    struct node_s * next;
    CPointer value;
} CSNode;

typedef struct list_s {
    CSNode * head;
    CSNode * last;
    size_t value_size;
} CSList;

CSList * CSList_alloc(size_t value_size);

CPointer * CSList_to_array_of_pointers(CSList * list);
 
CPointer CSList_at_ref(CSList * list, int index);
CPointer CSList_at_or_ref(CSList * list, int index, CPointer val);


void CSList_free_nodes(CSList * list);
void CSList_free_nodes_and_values(CSList * list);
void CSList_free_nodes_fun(CSList * list, void (*f)(CPointer *));

CSList * CSList_copy_nodes(CSList * list);
CSList * CSList_copy_nodes_and_values(CSList * list);

CSNode * CSList_last_node(CSList * list);

int CSList_empty(CSList * list);

void CSList_prepend_cpy(CSList * list, CPointer val);
void CSList_append_cpy(CSList * list, CPointer val);
void CSList_prepend_ref(CSList * list, CPointer val);
void CSList_append_ref(CSList * list, CPointer val);

CSList * CSList_reverse_ref(CSList * list);

int CSList_iter(CSList * list, void (*f)(CPointer val));
int CSList_iteri(CSList * list, void (*f)(CPointer val, int index));
CSList * CSList_map_ref(CSList * list, size_t dest_size, CPointer (*f)(CPointer val));
CSList * CSList_mapi_ref(CSList * list, size_t dest_size, CPointer (*f)(CPointer val, int));

C2Tuple * CSList_partition_ref(CSList * list, int (*f)(CPointer));
CSList * CSList_select_ref(CSList * list, int (*f)(CPointer));
CSList * CSList_reject_ref(CSList * list, int (*f)(CPointer));

CSList * CSList_zip2_ref(CSList * fst, CSList * snd);

CPointer * CSList_reduce_ref(CSList * list, CPointer init, size_t init_size, CPointer (*f)(CPointer, CPointer));

unsigned int CSList_length(CSList * list);

#endif