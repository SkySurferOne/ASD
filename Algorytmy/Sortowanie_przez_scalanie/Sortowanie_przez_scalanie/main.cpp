#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct node {
	int key;
	node * next;
};

int * r(int n) {
	int * t = new int[n];
	for (int i = 0; i<n; i++)
		t[i] = rand() % 50;
	return t;
}

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

bool add(node * &head, int key, bool guard = false) {
	node * tmp = new node;
	if (tmp == NULL) return false;
	tmp->key = key;
	if (guard) {
		tmp->next = head->next;
		head->next = tmp;
	} else {
		tmp->next = head;
		head = tmp;
	}
	return true;
}

void fillList(node * &head, int tab[], int n, bool guard = false) {
	for (int i = n - 1; i >= 0; i--)
		if (!add(head, tab[i], guard)) break;
}

void showList(node * head, bool guard = false) {
	if (guard) head = head->next;
	while (head != NULL) {
		cout << head->key << " -> ";
		head = head->next;
	}
	cout << endl;
}

// na wskaŸnikach
node * merge(node * l1, node * l2) {
	node * l3, *t3;
	l3 = t3 = new node;

	while (l1 != NULL && l2 != NULL) {
		if (l1->key < l2->key) {
			node * tmp = l1;
			l1 = l1->next;
			tmp->next = NULL;
			t3->next = tmp;
			t3 = tmp;
		} else {
			node * tmp = l2;
			l2 = l2->next;
			tmp->next = NULL;
			t3->next = tmp;
			t3 = tmp;
		}
	}

	if (l1 != NULL) {
		t3->next = l1;
		l1 = NULL;
	}
	if (l2 != NULL) {
		t3->next = l2;
		l2 = NULL;
	}

	node * tmp = l3;
	l3 = l3->next;
	delete tmp;
	t3 = NULL;
	return l3;
}

// funkcja znajduje œrodek w czasie liniowym
node * mid(node * l1) {
	int m, i;
	m = 0; i = 1;
	node * c = l1;
	while (l1 != NULL) {
		m++;
		l1 = l1->next;
	}
	m /= 2;
	while (c != NULL && i < m) {
		i++;
		c = c->next;
	}
		
	return c;
}

// msort 1
node * msort(node * l1) {
	if (l1 == NULL || l1->next == NULL) return l1;
	node * tmp = mid(l1);
	node * l2 = tmp->next;
	tmp->next = NULL;

	node * l3 = msort(l1);
	node * l4 = msort(l2);

	return merge(l3, l4);
}

void init(node * &list, int n) {
	list = NULL;
	int * tab = r(n);
	fillList(list, tab, n);
	showList(list);
}

// na wskaŸnikach (wersja z æwiczeñ)

// wyci¹ga seriê naturaln¹ z head i podstawia ja pod s (obie listy musz¹ mieæ wartownika)
void nserie(node * head, node * s) { // lista nie mo¿e byæ pusta 
	node * tmp = head->next;
	while (tmp->next != NULL && tmp->next->key >= tmp->key)
		tmp = tmp->next;
	s->next = head->next;
	head->next = tmp->next;
	tmp->next = NULL;
}

// merge na listach z wartownikami, zwraca wsk na koniec posortowanej listy
node * merge_series(node * s1, node * s2, node * appendTo) {
	node * end = appendTo;
	while (s1->next != NULL && s2->next != NULL) {
		if (s1->next->key <= s2->next->key) {
			end->next = s1->next;
			end = end->next;
			s1->next = s1->next->next;
			end->next = NULL;
		} else {
			end->next = s2->next;
			end = end->next;
			s2->next = s2->next->next;
			end->next = NULL;
		}
	}

	if (s1->next != NULL) {
		end->next = s1->next;
		s1->next = NULL;
	} else if (s2->next != NULL) {
		end->next = s2->next;
		s2->next = NULL;
	}

	while (end->next != NULL) {
		end = end->next;
	}

	return end;
}

void msort2(node * head) {
	node * s1 = new node;
	s1->next = NULL;
	node * s2 = new node;
	s2->next = NULL;
	node * l = new node;
	l->next = NULL;
	node * end = l;

	int n;
	do {
		n = 0;
		while (head->next != NULL) {
			nserie(head, s1); 
			n++;
			if (head->next != NULL) {
				nserie(head, s2);
				n++;
				end = merge_series(s1, s2, end);
			} else {
				end->next = s1->next;
				s1->next = NULL;
			}
		}
		head->next = l->next;
		l->next = NULL;
		end = l;
	} while (n > 2);

	delete l;
	delete s1;
	delete s2;
}

void init2(node * &list, int n) {
	list = new node;
	list->next = NULL;
	int * tab = r(n);
	fillList(list, tab, n, true);
	showList(list, true);
}

// na tablicach
void mergeTab(int tab[], int l1, int m, int r2, int N) {
	int p = l1;
	int * T2 = new int[N];
	int r1 = m;
	int l2 = m + 1;
	int  i = l1;
	while (l1 <= r1 && l2 <= r2) {
		if (tab[l1] < tab[l2])
			T2[i] = tab[l1++];
		else
			T2[i] = tab[l2++];
		i++;
	}

	while (l1 <= r1)
			T2[i++] = tab[l1++];
	while (l2 <= r2)
			T2[i++] = tab[l2++];
	for (i = p; i <= r2; i++)
		tab[i] = T2[i];
}

void msortTab(int tab[], int l, int r, int n) {
	if (l < r) {
		int m = (l + r) / 2;
	    msortTab(tab, l, m, n);
		msortTab(tab, m + 1, r, n);
		mergeTab(tab, l, m, r, n);
	}
}

int main() {
	int n;
	node * list;
	cout << "Podaj n: ";
	cin >> n;
	init(list, n);
	list = msort(list);
	showList(list);

	// 
	cout << "list2" << endl;
	node * list2;
	init2(list2, n);
	msort2(list2);
	showList(list2, true);

	//
	int * tab = r(n);
	show(tab, n);
	msortTab(tab, 0, n - 1, n);
	show(tab, n);

	system("pause");
	return 0;
}