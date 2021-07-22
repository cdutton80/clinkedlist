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

CSList * CSList_find_ref(CSList * list, int (*f)(CPointer)) {
	CSList * result = CSList_alloc(sizeof(C2Tuple));
	
	CSNode * cur;
	int index;
	
	for (index = 0, cur = list->head; cur != NULL; index++, cur = cur->next) {
		if (f(cur->value)) {
			int * i = malloc(sizeof(int));
			*i = index;
			C2Tuple * match = malloc(sizeof(C2Tuple));
			match->fst = i;
			match->snd = cur->value;
			
			CSList_append_ref(result, match);
		}
	}
	
	return result;
}

C2Tuple * CSList_find_first_ref(CSList * list, int (*f)(CPointer)) {
	CSList * found = CSList_find_first_n_ref(list, 1, f);
	if (CSList_empty(found)) {
		return NULL;
	}
	else {
		C2Tuple * result = found->head->value;
		CSList_free_nodes(found);
		free(found);
		
		return result;
	}
}

CSList * CSList_find_first_n_ref(CSList * list, int n, int (*f)(CPointer)) {
	CSList * result = CSList_alloc(sizeof(C2Tuple));
	
	CSNode * cur;
	int index;
	int count;
	
	for (count = 1, index = 0, cur = list->head; count <= n && cur != NULL; index++, cur = cur->next) {
		if (f(cur->value)) {
			int * i = malloc(sizeof(int));
			*i = index;
			C2Tuple * match = malloc(sizeof(C2Tuple));
			match->fst = i;
			match->snd = cur->value;
			
			CSList_append_ref(result, match);
			count++;
		}
	}
	
	return result;
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

void CSList_iter2(CSList * list1, CSList * list2, void (*f)(CPointer, CPointer)) {
	int len1 = CSList_length(list1);
	int len2 = CSList_length(list2);
	
	if (len1 != len2 && len1 > 0) {
		return;
	}
	else {
		CSNode * cur1, * cur2;
		for (cur1 = list1->head, cur2 = list2->head; cur1 != NULL && cur2 != NULL; cur1 = cur1->next, cur2 = cur2->next) {
			f(cur1->value, cur2->value);
		}
	}
}

void CSList_iter2i(CSList * list1, CSList * list2, void (*f)(CPointer, CPointer, int)) {
	int len1 = CSList_length(list1);
	int len2 = CSList_length(list2);
	
	if (len1 != len2 && len1 > 0) {
		return;
	}
	else {
		CSNode * cur1, * cur2;
		int i;
		for (i = 0, cur1 = list1->head, cur2 = list2->head; cur1 != NULL && cur2 != NULL; i++, cur1 = cur1->next, cur2 = cur2->next) {
			f(cur1->value, cur2->value, i);
		}
	}
}

void CSList_iter_where(CSList * list, void (*f)(CPointer), int (*p)(CPointer)) {
	if (!CSList_empty(list)) {
        CSNode * cur;
        for (cur = list->head; cur != NULL; cur = cur->next) {
            if (p(cur->value)) {
            	f(cur->value);
            }
        }
    }
}

void CSList_rev_iter(CSList * list, void (*f)(CPointer val)) {
	CSList * rev = CSList_reverse_ref(list);
	CSList_iter(rev, f);
	CSList_free_nodes(rev);
	free(rev);
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

CSList * CSList_map2_ref(CSList * list1, CSList * list2, size_t dest_size, CPointer (*f)(CPointer, CPointer)) {
	CSList * result = CSList_alloc(dest_size);
	CSNode * cur1, *cur2;

	for (cur1 = list1->head, cur2 = list2->head; cur1 != NULL && cur2 != NULL; cur1 = cur1->next, cur2 = cur2->next) {
		CPointer fresult = f(cur1->value, cur2->value);
		CSList_append_ref(result, fresult);
	}

	if (cur1 == NULL && cur2 == NULL) {
		return result;
	}
	else {
		CSList_free_nodes_and_values(result);
		free(result);
		return NULL;
	}
}

CSList * CSList_map2i_ref(CSList * list1, CSList * list2,  size_t dest_size, CPointer (*f)(CPointer, CPointer, int)) {
	CSList * result = CSList_alloc(dest_size);
	CSNode * cur1, *cur2;
	int i;

	for (i = 0, cur1 = list1->head, cur2 = list2->head; cur1 != NULL && cur2 != NULL; i++, cur1 = cur1->next, cur2 = cur2->next) {
		CPointer fresult = f(cur1->value, cur2->value, i);
		CSList_append_ref(result, fresult);
	}

	if (cur1 == NULL && cur2 == NULL) {
		return result;
	}
	else {
		CSList_free_nodes_and_values(result);
		free(result);
		return NULL;
	}
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

int CSList_length(CSList * list) {
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

CSList * CSList_concat_ref(CSList * list1, CSList * list2) {
	if (list1 == NULL && list2 == NULL) {
		return NULL;
	}
	else if (list1 == NULL && list2 != NULL) {
		return CSList_copy_nodes(list2);
	}
	else if (list1 != NULL && list2 == NULL) {
		return CSList_copy_nodes(list1);
	}
	else if (list1->value_size != list2->value_size) {
		return NULL;
	}
	else {
		CSNode * cur2;
		CSList * result = CSList_copy_nodes(list1);
		for (cur2 = list2->head; cur2 != NULL; cur2 = cur2->next) {
			CSList_append_ref(result, cur2->value);
		}
		
		return result;
	}
}

CSList * CSList_intersperse2_ref(CSList * list1, CSList * list2) {
	if (list1 == NULL && list2 == NULL) {
		return NULL;
	}
	else if (list1 == NULL && list2 != NULL) {
		return NULL;
	}
	else if (list1 != NULL && list2 == NULL) {
		return NULL;
	}
	else if (list1->value_size != list2->value_size) {
		return NULL;
	}
	else {
		CSNode * cur1, * cur2;
		CSList * result = CSList_alloc(list1->value_size);
		for (cur1 = list1->head, cur2 = list2->head; cur1 != NULL && cur2 != NULL; cur1 = cur1->next, cur2 = cur2->next) {
			CSList_append_ref(result, cur1->value);
			CSList_append_ref(result, cur2->value);
		}
		
		if (cur1 == NULL && cur2 == NULL) {
			return result;
		}
		else {
			CSList_free_nodes(result);
			return NULL;
		}	
	}
}

CPointer CSList_minimum_value(CSList * list, int (*f)(CPointer, CPointer)) {
	if (list == NULL || CSList_empty(list)) {
		return NULL;
	}
	else {
		CPointer smallest = list->head->value;
		
		for (CSNode * cur = list->head->next; cur != NULL; cur = cur->next) {
			if (f(cur->value, smallest) == -1) {
				smallest = cur->value;
			}
		}
		
		return smallest;
	}
}

CPointer CSList_maximum_value(CSList * list, int (*f)(CPointer, CPointer)) {
	if (list == NULL || CSList_empty(list)) {
		return NULL;
	}
	else {
		CPointer largest = list->head->value;
		
		for (CSNode * cur = list->head->next; cur != NULL; cur = cur->next) {
			if (f(cur->value, largest) == 1) {
				largest = cur->value;
			}
		}
		
		return largest;
	}
}

CSList * CSList_sort_ref(CSList * list, int (*f)(CPointer, CPointer)) {
	if (list == NULL || CSList_empty(list)) {
		return NULL;
	} 
	else if (CSList_cmp_len_with(list, 1) == 0) {
		return CSList_copy_nodes(list);
	}
	else {
		CSList * result = CSList_copy_nodes(list);
		CSNode * node = result->head;
		CSNode * temp;

		while (node != NULL) {
			temp = node;
			while (temp != NULL) {
				if(f(node->value, temp->value) == 1) {
					CPointer v = node->value;
					node->value = temp->value;
					temp->value = v;
				}
				temp = temp->next;
			}
			
			node = node->next;
		}

		return result;
	}
}

int CSList_has(CSList * list, int (*f)(CPointer)) {
	if (list == NULL || CSList_empty(list)) {
		return 0;
	}
	else {
		for (CSNode * cur = list->head; cur != NULL; cur = cur->next) {
			if (f(cur->value)) {
				return 1;
			}
		}
		
		return 0;
	}
}

CSList * CSList_uniq_ref(CSList * list, int (*f)(CPointer, CPointer)) {
	if (list == NULL || CSList_empty(list)) {
		return NULL;
	}

	CSList * sorted = CSList_sort_ref(list, f);
	CSList * uniq = CSList_alloc(list->value_size);

	for (CSNode * cur = sorted->head; cur != NULL; cur = cur->next) {
		if (cur->next == NULL || f(cur->value, cur->next->value) != 0) {
			CSList_append_ref(uniq, cur->value);
		}
	} 

	CSList_free_nodes(sorted);
	free(sorted);

	return uniq;
}

int CSList_cmp_len_with(CSList * list, int len) {
	CSNode * cur = list->head;
	int count = 0;
	while (cur != NULL) {
		count++;
		if (count > len) {
			return 1;
		}
		else if (count == len && cur->next == NULL) {
			return 0;
		}

		cur = cur->next;
	}
	
	return -1;
}

CSList * CSList_group_by_ref(CSList * list, size_t key_size, CPointer (*keyf)(CPointer), int (*cmpf)(CPointer, CPointer)) {
	CSList * map = CSList_map_ref(list, key_size, keyf);
	CSList * uniq = CSList_uniq_ref(map, cmpf);
	CSList * result = CSList_alloc(sizeof(C2Tuple));

	CSList_free_nodes(map);
	free(map);

	for (CSNode * cur = uniq->head; cur != NULL; cur = cur->next) {
		C2Tuple * t = malloc(sizeof(C2Tuple));
		t->fst = cur->value;
		t->snd = CSList_alloc(list->value_size);

		for (CSNode * cur2 = list->head; cur2 != NULL; cur2 = cur2->next) {
			if (cmpf(t->fst, keyf(cur2->value)) == 0) {
				CSList_append_ref(t->snd, cur2->value);
			}
		}

		CSList * temp = t->snd;
		t->snd = CSList_sort_ref(t->snd, cmpf);
		CSList_free_nodes(temp);
		free(temp);

		CSList_append_ref(result, t);
	}

	return result;
}
