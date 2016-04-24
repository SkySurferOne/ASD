#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N = 12;
const int K = 10;

// 1. implementacja tablicowa 

// O(1) 
void makeSetTab(int i, int R[]) {
	R[i] = i;
}
// O(1)
int findTab(int i, int R[]) {
	return R[i];
}
// O(n)
void unionTab(int x, int y, int R[]) {
	int rx = findTab(x, R);
	int ry = findTab(y, R);
	if (rx != ry) {
		for (int i = 0; i < N; i++) {
			if (R[i] == ry)
				R[i] = rx;
		}
	}
}
// O(n)
void initTab(int R[]) {
	for (int i = 0; i < N; i++) {
		makeSetTab(i, R);
	}
}
// O(1)
bool isSameSetTab(int x, int y, int R[]) {
	return findTab(x, R) == findTab(y, R);
}

// 2. implementacja listowa
struct setNode;

struct set {
	setNode * head, * tail;
	int length; // pos³u¿y nam do ³¹czenia krótszej listy z wiêksz¹
};

struct setNode {
	set * r;
	setNode * next;
	int val;
};

// O(1)
set * findList(setNode * c) {
	return c->r;
}
// O(1)
setNode * makeSetList(int v) {
	set * s = new set;
	setNode * t = new setNode;
	t->r = s;
	t->next = NULL;
	t->val = v;
	s->head = s->tail = t;
	s->length = 1;
	return t;
}
// O(m) - gdzie m to liczba el. w mniejszej liœcie
void unionList(setNode * x, setNode * y) {
	set * rx = findList(x);
	set * ry = findList(y);
	if (rx != ry) {
		if (rx->length > ry->length) {
			rx->tail->next = ry->head;
			rx->tail = ry->tail;
			rx->length += ry->length;
			while (ry->head != NULL) {
				ry->head->r = rx;
				ry->head = ry->head->next;
			}
			delete ry;
		} else {
			ry->tail->next = rx->head;
			ry->tail = rx->tail;
			ry->length += rx->length;
			while (rx->head != NULL) {
				rx->head->r = ry;
				rx->head = rx->head->next;
			}
			delete rx;
		}
	}
}
// O(n)
void initList(setNode * tab[]) {
	for (int i = 0; i < N; i++) {
		tab[i] = makeSetList(rand() % 100);
	}
}
// 
void showSetsList(setNode * tab[]) {
	int c = 0;
	for (int i = 0; i < N; i++) {
		if (tab[i]->r->head == tab[i])
			c++;
	}
	cout << "Ilosc zbiorow: " << c << endl;
	for (int i = 0; i < N; i++) {
		if (tab[i]->r->head == tab[i]) {
			for (int j = 0; j < N; j++) {
				if (tab[j]->r->head == tab[i])
					cout << tab[j]->val << " ";
			}
			cout << endl;
		}
	}
}

// 3. implementacja na drzewie
struct node {
	node * up;
	int val, rank;
};
// O(1)
node * makeSetTree(int v) {
	node * s = new node;
	s->up = s;
	s->rank = 0;
	s->val = v;
	return s;
}
// 
node * findTree(node * s) {
	if (s->up != s) {
		node * y = findTree(s->up);
		s->up = y;
		return y;
	} else {
		return s;
	}
}
//
void unionTree(node * x, node * y) {
	node * rx = findTree(x);
	node * ry = findTree(y);
	if (rx->rank > ry->rank) {
		ry->up = rx;
	} else {
		rx->up = ry;
		if (ry->rank == rx->rank)
			ry->rank++;
	}
}
//
void initTree(node * tab[]) {
	for (int i = 0; i < N; i++) {
		tab[i] = makeSetTree(rand() % 100);
	}
}
//
void showSetsTree(node * tab[]) {
	int c = 0;
	for (int i = 0; i < N; i++) {
		if (findTree(tab[i]) == tab[i])
			c++;
	}
	cout << "Ilosc zbiorow: " << c << endl;
	for (int i = 0; i < N; i++) {
		if (findTree(tab[i]) == tab[i]) {
			for (int j = 0; j < N; j++) {
				if (findTree(tab[j]) == tab[i])
					cout << tab[j]->val << " ";
			}
			cout << endl;
		}
	}
}

int main() {
	srand(time(NULL));

	// 1. test
	int R[N];
	initTab(R);
	unionTab(7, 1, R);
	unionTab(1, 2, R);

	unionTab(10, 6, R);
	unionTab(8, 10, R);

	unionTab(9, 0, R);
	unionTab(11, 5, R);
	unionTab(11, 9, R);

	unionTab(4, 3, R);
	
	cout << isSameSetTab(1, 7, R) << endl;
	cout << isSameSetTab(10, 8, R) << endl;
	cout << isSameSetTab(3, 2, R) << endl;
	cout << endl;

	// 2. test
	setNode * T[N];
	initList(T);
	// O(K * m)
	for (int i = 0; i < K; i++) {
		unionList(T[rand() % N], T[rand() % N]);
	}
	showSetsList(T);
	cout << endl;

	// 3. test
	node * U[N];
	initTree(U);
	for (int i = 0; i < K; i++) {
		unionTree(U[rand() % N], U[rand() % N]);
	}
	showSetsTree(U);

	system("pause");
	return 0;
}