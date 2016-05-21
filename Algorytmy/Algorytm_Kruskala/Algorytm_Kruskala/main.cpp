#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
using namespace std;
#define V_SIZE 8

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  6  7    
	{ -1, 5, 0, 9, 0, 0, 3, 0 },  // 0
	{ 0, -1, 9, 0, 8, 6, 0, 7 },  // 1
	{ 0,  0, -1, 9, 4, 0, 5, 3 }, // 2
	{ 0,  0, 0, -1, 0, 0, 8, 0 }, // 3
	{ 0,  0, 0, 0, -1, 2, 1, 0 }, // 4
	{ 0,  0, 0, 0, 0, -1, 6, 0 }, // 5
	{ 0,  0, 0, 0, 0, 0, -1, 9 }, // 6  
	{ 0,  0, 0, 0, 0, 0, 0, -1 }  // 7  
};

struct edge {
	int v, u, w;
};

// find and union
inline void makeSet(int * tab, int i) {
	tab[i] = i;
}

inline int findSet(int * tab, int i) {
	return tab[i];
}

void unionSets(int R[], int x, int y) {
	int rx = findSet(R, x);
	int ry = findSet(R, y);
	if (rx != ry) {
		for (int i = 0; i < V_SIZE; i++) {
			if (R[i] == ry)
				R[i] = rx;
		}
	}
}

struct compareWeights {
	bool operator()(const edge &l, const edge &r) {
		return l.w > r.w;
	}
};

// it destroys queue
void showQueue(priority_queue<edge, vector< edge >, compareWeights> queue) {
	while (!queue.empty()) {
		cout << queue.top().v << "-" << queue.top().u << ":" << queue.top().w << endl;
		queue.pop();
	}
}

void show(int * tab, int n) {
	for (int i = 0; i < n; i++)
		cout << i << ": "<< tab[i] << endl;
	cout << endl;
}

template <size_t size>
priority_queue<edge, vector< edge >, compareWeights>
kruskal(int(&g)[size][size]) {
	priority_queue<edge, vector< edge >, compareWeights> Q, T; // krawêdzie wdlg wag
	int Z[size]; // tablica reprezentantów 

	for (int v = 0; v < size; v++) {
		makeSet(Z, v);

		for (int u = 0; u < size; u++) {
			if (g[v][u] > 0) {
				edge e = { v, u, g[v][u] };
				Q.push(e);
			}
		}
	}
	
	for (int i = 0; i < size-1; i++) {
		edge e;
		do {
			e = Q.top(); Q.pop();
		} while (findSet(Z, e.v) == findSet(Z, e.u));
		T.push(e);
		unionSets(Z, e.v, e.u);
	}
	
	return T;
}

int main() {
	showQueue(kruskal(graph));

	system("pause");
	return 0;
}