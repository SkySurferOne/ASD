#include <iostream>
#include "msort_bidirlist.hpp"
using namespace std;

node2 * getlast(node2 * l) {
	while (l != NULL && l->next != NULL)
		l = l->next;
	return l;
}

void showbidir(node2 * l, int dir) {
	while (dir == 0 && l != NULL) {
		cout << l->key << "->";
		l = l->next;
	}
	while (dir == 1 && l != NULL) {
		cout << l->key << "->";
		l = l->prev;
	}
	cout << endl;
}

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
	if(head != NULL) head->prev = NULL;
};

// appendTo musi mieæ wartownika
node2 * merge_series2(node2 * &s1, node2 * &s2, node2 * appendTo) {
	node2 * end = appendTo;
	while (s1 != NULL && s2 != NULL) {
		if (s1->key <= s2->key) {
			node2 * tmp = s1;
			s1 = s1->next; 
			if(s1 != NULL) s1->prev = NULL;
			tmp->next = NULL;
			tmp->prev = end;
			end->next = tmp;
			end = tmp;
			
		} else {
			node2 * tmp = s2;
			s2 = s2->next;
			if (s2 != NULL) s2->prev = NULL;
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

}

void msort_bidirlist(node2 * &head) {
	node2 * s1 = NULL;
	node2 * s2 = NULL;
	node2 * l = new node2;
	l->next = l->prev = NULL;
	node2 * end = l;

	int n;
	do {
		n = 0;
		while (head != NULL) {
			nserie2(head, s1);
			n++;
			if (head != NULL) {
				nserie2(head, s2);
				n++;
				end = merge_series2(s1, s2, end);
			}
			else {
				end->next = s1;
				s1->prev = end;
			}
		}
		head = l->next;
		head->prev = NULL;
		l->next = NULL;
		end = l;
	} while (n > 2);

	delete l;
}