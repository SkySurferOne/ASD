#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAX_H 4

struct SLNode {
	int val, height;
	SLNode * next[MAX_H];

	SLNode() {
		for (int i = 0; i < MAX_H; i++)
			this->next[i] = NULL;
	}
};

struct SkipList {
	SLNode * head;
	int height;
};

// 
int getHeight() {

	int h = 1;

	while (h < MAX_H && rand() < RAND_MAX/2)
		h++;

	return h;
}

//
SLNode * newNode(int key) {
	SLNode * tmp = new SLNode;
	tmp->val = key;
	tmp->height = getHeight();
	return tmp;
}

//
int find(SkipList * skip, int key) {
	SLNode * it = skip->head;

	for (int i = skip->height - 1; i >= 0; i--) 
		while (it->next[i] != NULL && key > it->next[i]->val)
			it = it->next[i];

	return it->next[0] ? it->next[0]->val : -1;
}

//
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
	
	if (it->next[0] != NULL && it->next[0]->val == key) {
		return 0;
	} else {

		if (item->height > skip->height) {
			for (int i = skip->height; i < item->height; i++) {
				fix[i] = skip->head;
			}

			skip->height = item->height;
		}

		for (int i = 0; i < item->height; i++) {
			item->next[i] = fix[i]->next[i];
			fix[i]->next[i] = item;
		}
	}

	return 1;
}

// 
void deleteNode() {

}

// 
void init(SkipList * skip) {
	skip->height = 1;
	SLNode * tmp = new SLNode;
	tmp->val = -INFINITY;
	tmp->height = 1;
	skip->head = tmp;
}

int main() {
	srand(time(NULL));
	SkipList * skip = new SkipList;
    init(skip);
	insert(skip, 11);
	insert(skip, 22);
	insert(skip, 33);
	insert(skip, 9);

	cout << find(skip,11) << endl;
	cout << find(skip, 22) << endl;
	cout << find(skip, 6) << endl;

	system("pause");
	return 0;
}