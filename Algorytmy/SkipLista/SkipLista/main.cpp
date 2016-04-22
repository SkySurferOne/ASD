#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// maksymalna wysokoœæ skip listy
#define MAX_H 4

struct SLNode {
	int val, height;
	SLNode * next[MAX_H];

	// domyœlnie tablica nastêpników musi zostaæ wype³niona NULLami
	SLNode() {
		for (int i = 0; i < MAX_H; i++)
			this->next[i] = NULL;
	}
};

struct SkipList {
	SLNode * head;
	int height;
};

// zwraca losow¹ liczbê rzeczywist¹ z przedzia³u [0, 1]
double rand48() {
	return (double) (double)rand() / (double)RAND_MAX;
}

// zwraca losow¹ wysokoœæ z przedzia³u [1, MAX_H]
int getHeight(double p = 1/2) {
	int h = 1;

	while (h < MAX_H && rand48() < p)
		h++;

	return h;
}

// tworzy nowy wêze³ z losow¹ wysokoœci¹
SLNode * newNode(int key) {
	SLNode * tmp = new SLNode;
	tmp->val = key;
	tmp->height = getHeight();
	return tmp;
}

// sprawdza czy istnieje element o kluczu key, jeœli nie, zwraca -1, wpp zwraca klucz
// normalnie funkcja powinna zwracaæ wskaŸnik na wêze³
int find(SkipList * skip, int key) {
	SLNode * it = skip->head;

	for (int i = skip->height - 1; i >= 0; i--) 
		while (it->next[i] != NULL && key > it->next[i]->val)
			it = it->next[i];

	return (it->next[0] != NULL && it->next[0]->val == key) ? it->next[0]->val : -1;
}

// dodaje element do skip listy
int insert(SkipList * skip, int key) {
	SLNode * it = skip->head;
	SLNode * item = newNode(key);
	SLNode * fix[MAX_H];
	memset(fix, NULL, sizeof(SLNode*) * (MAX_H));

	for (int i = skip->height - 1; i >= 0; i--) {
		while (it->next[i] != NULL && key > it->next[i]->val)
			it = it->next[i];
		fix[i] = it;
	}
	
	if (it->next[0] != NULL && it->next[0]->val == key)
		return 0;

	if (item->height > skip->height) {
		for (int i = skip->height; i < item->height; i++)
			fix[i] = skip->head;
		skip->height = item->height;
	}

	for (int i = 0; i < item->height; i++) {
		item->next[i] = fix[i]->next[i];
		fix[i]->next[i] = item;
	}
	
	return 1;
}

// usuwa element ze slip listy
void deleteNode(SkipList * skip, int key) {
	SLNode * it = skip->head;
	SLNode * fix[MAX_H];
	memset(fix, NULL, sizeof(SLNode*) * (MAX_H));

	for (int i = skip->height - 1; i >= 0; i--) {
		while (it->next[i] != NULL && key > it->next[i]->val)
			it = it->next[i];
		fix[i] = it;
	}

	if (it->next[0] == NULL || it->next[0]->val != key)
		return;

	SLNode * tmp = fix[0]->next[0];
	for (int i = 0; i < skip->height; i++)
		if (fix[i]->next[i] != NULL && fix[i]->next[i]->val == key)		
			fix[i]->next[i] = fix[i]->next[i]->next[i];

	while (skip->height > 0) {
		if (skip->head->next[skip->height - 1] != NULL)
			break;
		skip->head->next[--skip->height] = NULL;
	}

	delete tmp;
}

// inicjalizuje skip listê
void init(SkipList * skip) {
	skip->height = 1;
	SLNode * tmp = new SLNode;
	tmp->val = -INFINITY;
	tmp->height = 1;
	skip->head = tmp;
}

// wyœwietla klucze wszystkich wêz³ów w skip liœcie 
void show(SkipList * skip) {
	SLNode * s = skip->head;
	while (s->next[0] != NULL) {
		cout << s->next[0]->val << " ";
		s = s->next[0];
	}
	cout << endl;
}

int main() {
	srand(time(NULL));

	SkipList * skip = new SkipList;
    init(skip);

	// test skip listy
	insert(skip, 11);
	insert(skip, 22);
	insert(skip, 33);
	insert(skip, 9);

	show(skip);

	cout << find(skip,11) << endl;
	cout << find(skip, 22) << endl;
	cout << find(skip, 6) << endl;

	deleteNode(skip, 2);
	deleteNode(skip, 22);
	deleteNode(skip, 9);

	show(skip);

	insert(skip, 56);
	insert(skip, 722);
	insert(skip, 44);
	insert(skip, 229);

	cout << find(skip, 11) << endl;
	cout << find(skip, 22) << endl;
	cout << find(skip, 6) << endl;

	show(skip);

	system("pause");
	return 0;
}