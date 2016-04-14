#include <iostream>
#include <ctime>
#include <cstdlib>

#define MAX_H 4

struct SLNode {
	int val;
	SLNode * next[MAX_H];
};

struct SplitList {
	SLNode * head;
	int height;
};

// 
int getHeight() {
	srand(time(NULL));
	int h = 1;

	while (h < MAX_H && rand() < RAND_MAX/2)
		h++;

	return h;
}

//
void addNode() {

}

//
int search() {

}

//
int insert() {

}

// 
void deleteNode() {

}

int main() {
	

	return 0;
}