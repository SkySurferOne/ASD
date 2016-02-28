#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int * r(int n) {
	int * t = new int[n]; 
	for(int i=0; i<n; i++)
		t[i] = rand() % 50;
	return t; 
}

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

void bsort(int t[], int n) {
	bool war = false;
	for(int i=0; i<n; i++) {
		war = false;
		for(int j=0; j<n-1-i; j++) {
			if(t[j]>t[j+1]) {
				int tmp = t[j];
				t[j] = t[j+1];
				t[j+1] = tmp; 
				war = true;
			}
		}
		if (war) break;

	}
}

struct node {
	int key;
	node * next;
};

void insert(node * list, node * el) {
	while (list->next != NULL && list->next->key < el->key)
		list = list->next;
	el->next = list->next;
	list->next = el;
}

// lista nie mo¿e byæ pusta
node * removemax(node * first) {
	node * p_max = first;
	while (first->next != NULL) {
		if (p_max->next->key < first->next->key)
			p_max = first;
		first = first->next;
	}

	node * max = p_max->next;
	p_max->next = max->next;
	max->next = NULL;
	return max;
}

node * isort(node * first) {
	node * sorted = new node;
	sorted->next = NULL;
	while (first->next != NULL) {
		node * tmp = first->next;
		first->next = tmp->next;
		tmp->next = NULL;
		insert(sorted, tmp);
	}
	delete first;
	return sorted;
}

node * ssort(node * first) {
	node * sorted = new node;
	sorted->next = NULL;
	while (first->next != NULL) {
		node * tmp = removemax(first);
		tmp->next = sorted->next;
		sorted->next = tmp;
	}
	delete first;
	return sorted;
}

void  init(node * &head) {
	head = new node;
	head->next = NULL;
}

bool add(node * head, int key) {
	node * tmp = new node;
	if (tmp == NULL) return false;
	tmp->key = key;
	tmp->next = head->next;
	head->next = tmp;
	return true;
}

void fillList(node * head, int tab[], int n) {
	for (int i = n - 1; i >= 0; i--)
		if (!add(head, tab[i])) break;
}

void showList(node * head) {
	while (head->next != NULL) {
		cout << head->next->key << " ";
		head = head->next;
	}
	cout << endl;
}

void clearList(node * head) {
	while (head->next != NULL) {
		node * tmp = head->next;
		head->next = tmp->next;
		delete tmp;
	}
}

>>>>>>> f94e2fff10cb33bd5957389564f1ff160bb91740
int main() {
	srand(time(NULL));
	int n;
	cout << "Podaj n: ";
	cin >> n;
	int * tab = r(n);
	show(tab, n);
	bsort(tab, n);
	show(tab, n);
<<<<<<< HEAD
=======

	// sortowania na listach
	int * tab2 = r(n);
	node * head;
	init(head);
	fillList(head, tab2, n);
	showList(head);
	head = isort(head);
	showList(head);

	clearList(head);
	fillList(head, tab2, n);
	head = ssort(head);
	showList(head);

	system("pause");
>>>>>>> f94e2fff10cb33bd5957389564f1ff160bb91740
	return 0;
}