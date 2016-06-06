#include <iostream>
using namespace std;

#define V_SIZE 6

int vInd[V_SIZE]; // tablica stopni wchodz¹cych grafu

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5
	{ -1, 0, 1, 0, 0, 0 },
	{ 1, -1, 1, 0, 0, 0 },
	{ 0, 0, -1, 0, 0, 0 },
	{ 1, 1, 0, -1, 1, 0 },
	{ 0, 1, 1, 0, -1, 0 },
	{ 1, 0, 0, 0, 1, -1 }
};

struct vertex {
	int v;
	vertex * next;
};

vertex * makeList() {
	vertex * nlist, * tail; 
	nlist = tail = new vertex;

	for (int i = 0; i < V_SIZE; i++) {
		vertex * n = new vertex;
		n->v = i;
		tail->next = n;
		tail = n;
	}
	tail->next = NULL;
		
	return nlist;
}

void topoSort(int g[][V_SIZE]) {
	for (int i = 0; i < V_SIZE; i++)
		vInd[i] = 0; 

	for (int i = 0; i < V_SIZE; i++)
		for (int j = 0; j < V_SIZE; j++)
			if (g[i][j] == 1)
				vInd[j]++;

	bool test;
	vertex * list = makeList(); // z wartownikiem
	vertex * p;
	do {
		test = false;
		p = list;

		while (p->next != NULL) {
			if (vInd[p->next->v] > 0) {
				p = p->next;
				continue;
			}

			test = true; // znaleziono
			for (int i = 0; i < V_SIZE; i++)
				if (g[p->next->v][i] == 1)
					vInd[i]--;

			cout << p->next->v << endl;
			vertex * r = p->next;
			p->next = r->next;
			delete r;
		}
	} while (test);


}

int main() {
	topoSort(graph);

	system("pause");
	return 0;
}