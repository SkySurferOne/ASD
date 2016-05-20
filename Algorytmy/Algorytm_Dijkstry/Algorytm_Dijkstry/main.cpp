#include <iostream>       // std::cout
//#include <queue>          // std::priority_queue
//#include <vector>         // std::vector
//#include <functional>     // std::greater
using namespace std;
#define V_SIZE 6

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  
	{ -1, 3, 0, 0, 3, 0 }, // 0
	{ 0, -1, 1, 0, 0, 0 }, // 1
	{ 0, 0, -1, 3, 0, 1 }, // 2
	{ 0, 3, 0, -1, 0, 0 }, // 3
	{ 0, 0, 0, 0, -1, 2 }, // 4
	{ 6, 0, 1, 0, 0, -1 }  // 5  
};

int d[V_SIZE]; // koszty dojœcia
int p[V_SIZE]; // tablica poprzedników
int S[V_SIZE];
int Q[V_SIZE];


bool qEmpty() {
	for (int i = 0; i < V_SIZE; i++) 
		if (Q[i]) return false;
	return true;
}

int getMinD() {
	int min = INT16_MAX;
	for (int i = 0; i < V_SIZE; i++) {
		if (d[i] < min) min = i;
	} 
	return min;
}

void show(int * tab, int length) {
	for (int i = 0; i < length; i++) {
		cout << i << ": " << tab[i] << " ";
	}
	cout << endl;
}

template <size_t size>
void pathProcess(int(&g)[size][size], int v) {
	for (int i = 0; i < size; i++) {
		S[i] = 0;
		Q[i] = 1;
		d[i] = INT16_MAX;
		p[i] = -1;
	}
	d[v] = 0;

	cout << qEmpty() << endl;
	cout << getMinD() << endl;
	show(d, V_SIZE);
	show(p, V_SIZE);

	while (!qEmpty()) {
		int u = getMinD();
		Q[u] = 0;
		S[u] = 1;
		for (int i = 0; i < size; i++) {
			if (i == u && g[u][i] == 0 && Q[i] == 0) continue;
			if (d[i] > d[u] + g[u][i]) {
				d[i] = d[u] + g[u][i];
				p[i] = u;
			}
		}
	}
}


int main() {
	int v = 0;
	pathProcess(graph, v);
	show(d, V_SIZE);
	show(p, V_SIZE);

	system("pause");
	return 0;
}