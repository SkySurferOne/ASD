#pragma once
#ifndef msort_bidirlist_h
#define msort_bidirlist_h

struct node2 {
	int key;
	node2 * next;
	node2 * prev;
};

struct w {
	node2 * next;
};

struct info {
	node2 head;
	node2 tail;
};

void nserie2(node2 * head, node2 * s);
void merge_series2(node2 * s1, node2 * s2, node2 * appendTo);
void msort_bidirlist(node2 * head);


#endif