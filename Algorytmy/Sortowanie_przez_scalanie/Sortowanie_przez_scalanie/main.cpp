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

bool add(node * &head, int key) {
	node * tmp = new node;
	if (tmp == NULL) return false;
	tmp->key = key;
	tmp->next = head;
	head = tmp;
	return true;
}

void fillList(node * &head, int tab[], int n) {
	for (int i = n - 1; i >= 0; i--)
		if (!add(head, tab[i])) break;
}

void showList(node * head) {
	while (head != NULL) {
		cout << head->key << " -> ";
		head = head->next;
	}
	cout << endl;
}

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

node * ssort(node * l1) {
	if (l1 == NULL || l1->next == NULL) return l1;
	node * tmp = mid(l1);
	node * l2 = tmp->next;
	tmp->next = NULL;

	node * l3 = ssort(l1);
	node * l4 = ssort(l2);

	return merge(l3, l4);
}

void init(node * &list, int n) {
	list = NULL;
	int * tab = r(n);
	fillList(list, tab, n);
	showList(list);
}

int main() {
	int n;
	node * list;
	cout << "Podaj n: ";
	cin >> n;
	init(list, n);
	list = ssort(list);
	showList(list);

	system("pause");
	return 0;
}