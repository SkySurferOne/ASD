#include <iostream>
using namespace std;

#define V_SIZE 6

int visited[V_SIZE];
int timetab[V_SIZE]; // etykiety czasowe przy powrocie (po przetworzeniu)
int parent[V_SIZE];

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	{ -1, 1, 0, 1, 0, 0 },
	{ 0, -1, 1, 1, 1, 0 },
	{ 0, 0, -1, 1, 0, 1 },
	{ 0, 0, 0, -1, 0, 1 },
	{ 0, 0, 0, 0, -1, 1 },
	{ 0, 0, 0, 0, 0, -1 }
};

void DFSVisit(int graph[][V_SIZE], int v, int &timevar, void(*action)(int, int)) {
	visited[v] = true;
	for (int i = 0; i<V_SIZE; i++) {
		if (graph[v][i] == 1 && !visited[i]) {
			parent[i] = v;
			DFSVisit(graph, i, timevar, action);
		}
	}
	action(v, timevar);

	timevar = timevar + 1;
	timetab[v] = timevar;
}

void DFS(int graph[][V_SIZE], void(*action)(int, int)) {
	for (int i = 0; i<V_SIZE; i++) {
		visited[i] = false;
		timetab[i] = -1;
	}
	int timevar = 0;

	for (int i = 0; i<V_SIZE; i++) {
		if (!visited[i])
			DFSVisit(graph, i, timevar, action);
	}
}

void printVertex(int v, int t) {
	printf("vertex: %d, time: %d\n", v, t);
}

int main() {
	DFS(graph, printVertex);

	system("pause");
	return 0;
}