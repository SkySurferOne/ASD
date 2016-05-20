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
	{ 6, 0, 0, 1, 0, -1 }  // 5  
};

int d[V_SIZE]; // koszty dojœcia
int p[V_SIZE]; // tablica poprzedników
bool visited[V_SIZE];

int getMinD() {
	int min_v, i;
	for (i = 0; i < V_SIZE && visited[i]; i++);
	min_v = i;
	for (; i < V_SIZE; i++) {
		if (!visited[i] && d[i] < d[min_v])
			min_v = i;
	}
	return min_v;
}

void show(int * tab, int length) {
	for (int i = 0; i < length; i++) {
		cout << i << ": " << tab[i] << endl;
	}
	cout << endl;
}

void showShortestPath(int * parents, int length, int dest) {
	if (dest != -1 && length-1 >= 0) {
		showShortestPath(parents, length-1, parents[dest]);
		cout << dest << endl;
	}
}

template <size_t size>
void pathProcess(int(&g)[size][size], int v) {
	for (int i = 0; i < size; i++) {
		visited[i] = false;
		d[i] = INT16_MAX;
		p[i] = -1;
	}
	d[v] = 0;
	int num_vis = 0;

	while (num_vis < size) {
		int u = getMinD();
		for (int i = 0; i < size; i++) {
			if (g[u][i] <= 0) continue;
			if (d[i] > d[u] + g[u][i]) {
				d[i] = d[u] + g[u][i];
				p[i] = u;
			}
		}
		visited[u] = true;
		num_vis++;
	}
}

int main() {
	int v = 0;
	pathProcess(graph, v);
	show(d, V_SIZE);
	show(p, V_SIZE);
	showShortestPath(p, V_SIZE, 3);

	system("pause");
	return 0;
}