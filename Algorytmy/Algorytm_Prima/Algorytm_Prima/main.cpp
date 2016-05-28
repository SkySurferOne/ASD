#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
using namespace std;
#define V_SIZE 8

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4  5  6  7    
	{ -1, 5, 0, 9, 0, 0, 3, 0 },  // 0
	{ 5, -1, 9, 0, 8, 6, 0, 7 },  // 1
	{ 0,  9, -1, 9, 4, 0, 5, 3 }, // 2
	{ 9,  0, 9, -1, 0, 0, 8, 0 }, // 3
	{ 0,  8, 4, 0, -1, 2, 1, 0 }, // 4
	{ 0,  6, 0, 0, 2, -1, 6, 0 }, // 5
	{ 3,  0, 5, 8, 1, 6, -1, 9 }, // 6  
	{ 0,  7, 3, 0, 0, 0, 9, -1 }  // 7  
};

struct edge {
	int v, u, w;
};

struct compareWeights {
	bool operator()(const edge &l, const edge &r) {
		return l.w > r.w;
	}
};

template <size_t size>
priority_queue<edge, vector< edge >, compareWeights> 
prima(int(&g)[size][size], int v) {
	priority_queue<edge, vector< edge >, compareWeights> Q, T; // krawêdzie wdlg wag
	bool * visited = new bool[size];
	for (int i = 0; i < size; i++)
		visited[i] = false;
	visited[v] = true;
	edge e;

	for (int i = 0; i < size-1; i++) {
		for (int u = 0; u < size; u++) {
			if (graph[v][u] <= 0) continue;
			if (!visited[u]) {
				e = { v, u, graph[v][u] };
				Q.push(e);
			}
		}

		do {
			e = Q.top(); Q.pop();
		} while (visited[e.u]);
		T.push(e);
		visited[e.u] = true;
		v = e.u;
	}

	delete[] visited;
	return T;
}

// it destroys queue
void showQueue(priority_queue<edge, vector< edge >, compareWeights> queue) {
	while (!queue.empty()) {
		cout << queue.top().v << "-" << queue.top().u << ":" << queue.top().w << endl;
		queue.pop();
	}
}

int main() {
	showQueue(prima(graph, 0));

	system("pause");
	return 0;
}