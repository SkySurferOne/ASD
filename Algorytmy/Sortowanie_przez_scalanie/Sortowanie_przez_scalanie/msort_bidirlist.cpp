#include <iostream>
#include "msort_bidirlist.h"

/* 
 * head jest wskaŸnikiem napierwszy el. listy 2 kier, s mo¿e byæ nullem
 * head nie mo¿e byæ nullem
 */
void nserie2(node2 * &head, node2 * &s) {
	node2 * tmp = head;
	while (tmp->next != NULL && tmp->next->key >= tmp->key)
		tmp = tmp->next;
	s = head;
	head = tmp->next;
	tmp->next = NULL;
	head->prev = NULL;
};

void fixempty(node2 * &l) {
	l = new node2;
	l->next = l->prev = NULL;
}

// appendTo musi mieæ wartownika
node2 * merge_series2(node2 * &s1, node2 * &s2, node2 * appendTo) {
	//if (appendTo == NULL) fixempty(appendTo);
	node2 * end = appendTo;
	while (s1 != NULL && s2 != NULL) {
		if (s1->key <= s2->key) {
			node2 * tmp = s1;
			s1 = s1->next; 
			s1->prev = NULL;
			tmp->next = NULL;
			tmp->prev = end;
			end->next = tmp;
			end = tmp;
			
		} else {
			node2 * tmp = s2;
			s2 = s2->next;
			s2->prev = NULL;
			tmp->next = NULL;
			tmp->prev = end;
			end->next = tmp;
			end = tmp;
		}
	}

	if (s1 != NULL) {
		s1->prev = end;
		end->next = s1;
		s1 = NULL;
	}
	else if (s2 != NULL) {
		s2->prev = end;
		end->next = s2;
		s2 = NULL;
	}

	while (end->next != NULL) {
		end = end->next;
	}

	return end;

};

/*

node2 a1, a2, a3, b1, b2;
// key, next, prev
node2 a1 = { 1, &a2, NULL };
node2 a2 = { 2, &a3, &a1 };
node2 a3 = { 3, NULL, &a2 };

node2 b1 = { 2, &b2, NULL };
node2 b2 = { 4, NULL, &b1 };

node2 * appendTo = new node2;
appendTo->next = appendTo->prev = NULL;
*/
