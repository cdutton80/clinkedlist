#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cslinkedlist.h"

CSList * CSList_alloc(size_t value_size) {
    CSList * result = malloc(sizeof(CSList));
    result->head = NULL;
    result->last = NULL;
    result->value_size = value_size;
    return result;
}

CPointer * CSList_to_array_of_pointers(CSList * list) {
	CPointer * result = malloc(CSList_length(list) * sizeof(CPointer));
	int i;
	CSNode * cur;
	for (i = 0, cur = list->head; cur != NULL; i++, cur = cur->next) {
		result[i] = cur->value;
	}
	return result;
}

CPointer CSList_at_ref(CSList * list, int index) {
    // CSNode * cur;
    // int i;
    // for (i = 0, cur = list->head; cur != NULL; i++, cur = cur->next) {
    //     if (i == index) {
    //         return cur->value;
    //     }
    // }
    // return NULL;
    
	return CSList_at_or_ref(list, index, NULL);
} 

CPointer CSList_at_or_ref(CSList * list, int index, CPointer val) {
	CSNode * cur;
    int i;
    for (i = 0, cur = list->head; cur != NULL; i++, cur = cur->next) {
        if (i == index) {
            return cur->value;
        }
    }
    return val;
}

void CSList_free_nodes(CSList * list) {
	CSNode * temp = list->head;
	while (temp != NULL) {
		CSNode * next = temp->next;
		free(temp);
		temp = next;
	}
	
	list->head = NULL;
	list->last = NULL;
}

void CSList_free_nodes_and_values(CSList * list) {
	CSNode * temp = list->head;
	while (temp != NULL) {
		CSNode * next = temp->next;
		free(temp->value);
		free(temp);
		temp = next;
	}
	
	list->head = NULL;
	list->last = NULL;
}

void CSList_free_nodes_fun(CSList * list, void (*f)(CPointer *)) {
	CSNode * temp = list->head;
	while (temp != NULL) {
		CSNode * next = temp->next;
		f(temp->value);
		free(temp);
		temp = next;
	}
	
	list->head = NULL;
	list->last = NULL;
}

CSList * CSList_copy_nodes(CSList * list) {
	CSList * result = CSList_alloc(list->value_size);
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		CSList_append_ref(result, cur->value);
	}

	return result;
}

CSList * CSList_copy_nodes_and_values(CSList * list) {
	CSList * result = CSList_alloc(list->value_size);
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		CSList_append_cpy(result, cur->value);
	}

	return result;
}

CSNode * CSList_last_node(CSList * list) {
	return list->last;
}

int CSList_empty(CSList * list) {
    return list->head == NULL;
}

void CSList_prepend_cpy(CSList * list, CPointer val) {
    CSNode * old_head = list->head;
    list->head = malloc(sizeof(CSNode));
    list->head->next = old_head;
    list->head->value = malloc(list->value_size);
    memcpy(list->head->value, val, list->value_size);
}

void CSList_append_cpy(CSList * list, CPointer val) {
    if (CSList_empty(list)) {
        list->head = malloc(sizeof(CSNode));
        list->head->next = NULL;
        list->last = list->head;
        list->head->value = malloc(list->value_size);
        memcpy(list->head->value, val, list->value_size);
    }
    else {
        CSNode * last = CSList_last_node(list);
        last->next = malloc(sizeof(CSNode));
        list->last = last->next;
        last->next->next = NULL;
        last->next->value = malloc(list->value_size);
        memcpy(last->next->value, val, list->value_size);
    }
}

void CSList_prepend_ref(CSList * list, CPointer val) {
    CSNode * old_head = list->head;
    list->head = malloc(sizeof(CSNode));
    list->head->next = old_head;
    list->head->value = val;
}

void CSList_append_ref(CSList * list, CPointer val) {
    if (CSList_empty(list)) {
        list->head = malloc(sizeof(CSNode));
        list->head->next = NULL;
        list->head->value = val;
        list->last = list->head;
    }
    else {
        CSNode * last = CSList_last_node(list);
        last->next = malloc(sizeof(CSNode));
        last->next->next = NULL;
        last->next->value = val;
        list->last = last->next;
    }
}

CSList * CSList_reverse_ref(CSList * list) {
	CSList * result = CSList_alloc(list->value_size);
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		CSList_prepend_ref(result, cur->value);
	}
	return result;
}

int CSList_iter(CSList * list, void (*f)(CPointer val)) {
    if (!CSList_empty(list)) {
        int count;
        CSNode * cur;
        for (count = 0, cur = list->head; cur != NULL; count++, cur = cur->next) {
            f(cur->value);
        }

        return count;
    }
    else {
        return -1;
    }
}

int CSList_iteri(CSList * list, void (*f)(CPointer val, int index)) {
	if (!CSList_empty(list)) {
        int count;
        CSNode * cur;
        for (count = 0, cur = list->head; cur != NULL; count++, cur = cur->next) {
            f(cur->value, count);
        }

        return count;
    }
    else {
        return -1;
    }
}

CSList * CSList_map_ref(CSList * list, size_t dest_size, CPointer (*f)(CPointer val)) {
	CSList * result = CSList_alloc(dest_size);
	
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		CPointer fresult = f(cur->value);
		CSList_append_ref(result, fresult);
	}

	return result;
}

CSList * CSList_mapi_ref(CSList * list, size_t dest_size, CPointer (*f)(CPointer val, int)) {
	CSList * result = CSList_alloc(dest_size);
	int i;
	CSNode * cur;
	
	for (i = 0, cur = list->head; cur != NULL; i++, cur = cur->next) {
		CPointer fresult = f(cur->value, i);
		CSList_append_ref(result, fresult);
	}

	return result;
}

C2Tuple * CSList_partition_ref(CSList * list, int (*f)(CPointer)) {
	CSList * trues = CSList_alloc(list->value_size);
	CSList * falses = CSList_alloc(list->value_size);
	
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		CSList_append_ref(f(cur->value) ? trues : falses, cur->value);
	}
	
	C2Tuple * result = malloc(sizeof(C2Tuple));
	result->fst = trues;
	result->snd = falses;
	
	return result;
}

CSList * CSList_select_ref(CSList * list, int (*f)(CPointer)) {
	CSList * trues = CSList_alloc(list->value_size);
	
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		if (f(cur->value)) {
			CSList_append_ref(trues, cur->value);
		}
	}
	
	return trues;
}

CSList * CSList_reject_ref(CSList * list, int (*f)(CPointer)) {
	CSList * falses = CSList_alloc(list->value_size);
	
	for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
		if (!f(cur->value)) {
			CSList_append_ref(falses, cur->value);
		}
	}
	
	return falses;
}

CSList * CSList_zip2_ref(CSList * fst, CSList * snd) {
	CSList * result = CSList_alloc(sizeof(C2Tuple));
	
	CSNode * cur1, * cur2;
	
	for (cur1 = fst->head, cur2 = snd->head; cur1 != NULL && cur2 != NULL; cur1 = cur1->next, cur2 = cur2->next) {
		C2Tuple * t = malloc(sizeof(C2Tuple));
		t->fst = cur1->value;
		t->snd = cur2->value;
		CSList_append_ref(result, t);
	}
	
	if (cur1 == NULL && cur2 == NULL) {
		return result;
	}
	else {
		return NULL;
	}
}

unsigned int CSList_length(CSList * list) {
	if (list == NULL) {
		return -1;
	}
	else {
		CSNode * cur;
		int len;
	
		for (cur = list->head, len = 0; cur != NULL; cur = cur->next, len++);
		
		return len;
	}
}

CPointer * CSList_reduce_ref(CSList * list, CPointer init, size_t init_size, CPointer (*f)(CPointer, CPointer)) {
	if (list == NULL) {
		return NULL;
	}
	else {
		CPointer result = init;
		CPointer prev_result = NULL;

		for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
			result = f(result, cur->value);

			if (prev_result == NULL) {
				prev_result = result;
			}
			else {
				free(prev_result);
				prev_result = result;
			}
		}

		return result;
	}

}