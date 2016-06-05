#include <iostream>
using namespace std;

#define V_SIZE 6

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	{ -1, 1, 0, 1, 0, 0 },
	{ 0, -1, 1, 1, 1, 0 },
	{ 0, 0, -1, 1, 0, 1 },
	{ 0, 0, 0, -1, 0, 1 },
	{ 0, 0, 0, 0, -1, 1 },
	{ 0, 0, 0, 0, 0, -1 }
};

bool visited[V_SIZE];
int parent[V_SIZE];

void DFSvisit(int g[][V_SIZE], int v) {
	visited[v] = true;

	for (int i = 0; i < V_SIZE; i++) {
		if (graph[v][i] == 1 && !visited[i]) {
			visited[i] = true;
			parent[i] = v;
			DFSvisit(g, i);
		}
	}
}

int DFS(int g[][V_SIZE]) {
	for (int i = 0; i < V_SIZE; i++) {
		visited[i] = false;
		parent[i] = -1;
	}
	
	int count = 0;
	for (int i = 0; i < V_SIZE; i++) {
		if (!visited[i]) {
			DFSvisit(graph, i);
			count++;
		}
	}
		
	return count;
}

int main() {
	cout << DFS(graph) << endl;

	system("pause");
	return 0;
}