#pragma once
#ifndef msort_bidirlist_hpp
#define msort_bidirlist_hpp

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

void nserie2(node2 * &head, node2 * &s);
node2 * merge_series2(node2 * &s1, node2 * &s2, node2 * appendTo);
void msort_bidirlist(node2 * &head);
void showbidir(node2 * l, int dir = 0);
node2 * getlast(node2 * l);


#endif