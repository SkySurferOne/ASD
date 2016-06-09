#include <iostream>       // std::cout
using namespace std;
#define V_SIZE 6

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  
	{ 0, 5, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX }, // 0
	{ INT16_MAX, 0, INT16_MAX, 3, 9, INT16_MAX }, // 1
	{ 3, -4, 0, INT16_MAX, INT16_MAX, INT16_MAX }, // 2
	{ INT16_MAX, INT16_MAX, INT16_MAX, 0, 3, 2 }, // 3
	{ INT16_MAX, INT16_MAX, -1, INT16_MAX, 0, -5 }, // 4
	{ 9, INT16_MAX, 8, INT16_MAX, INT16_MAX, 0 }  // 5  
};

int d[V_SIZE]; // koszty dojœcia
int p[V_SIZE]; // tablica poprzedników

template <size_t size>
bool BF(int(&g)[size][size], int s) {
	for (int i = 0; i < size; i++) {
		d[i] = INT16_MAX;
		p[i] = -1;
	}
	d[s] = 0;

	for (int i = 0; i < size - 1; i++) {
		bool test = true;
		for (int u = 0; u < size; u++) {
			for (int v = 0; v < size; v++) {
				if (g[u][v] == 0 || g[u][v] == INT16_MAX) continue;
				if (d[v] > d[u] + g[u][v]) {
					test = false;
					d[v] = d[u] + g[u][v];
					p[v] = u;
				}
			}
		}

		if (test) return true;
	}

	for (int u = 0; u < size; u++) 
		for (int v = 0; v < size; v++) 
			if (g[u][v] != 0 && g[u][v] != INT16_MAX && d[v] > d[u] + g[u][v]) 
				return false;
		
	return true;
}

void showShortestPath(int * parents, int length, int dest) {
	if (dest != -1 && length - 1 >= 0) {
		showShortestPath(parents, length - 1, parents[dest]);
		cout << dest << endl;
	}
}

int main() {
	int s = 0;
	BF(graph, s);
	showShortestPath(p, V_SIZE, 5);

	system("pause");
	return 0;
}