#include <iostream>
#include <queue>
using namespace std;
#define V_SIZE 6

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
				{-1, 1, 0, 1, 0, 0},
				{0, -1, 1, 1, 1, 0},
				{0, 0, -1, 1, 0, 1},
				{0, 0, 0, -1, 0, 1},
				{0, 0, 0, 0, -1, 1},
				{0, 0, 0, 0, 0, -1}
			};

template <size_t size>
void BFS(int (&g)[size][size], int vertex, void (* action)(int)) {
	queue< int > Q;
	bool * visited = new bool[size];
	int * parent = new int[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
		parent[i] = -1;
	}
	visited[vertex] = true;
	Q.push(vertex);
	action(vertex);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (g[u][i] == 1 && !visited[i]) {
				visited[i] = true;
				parent[i] = u;
				action(i);
				Q.push(i);
			}
		}
	}

	delete[] visited;
	delete[] parent;
}

void printVertex(int v) {
	cout << v << endl;
}

// reprezentacja listowa 
struct node {
	int v;
	node * next;
};

node ** graphList;

template <size_t size>
node ** makeListFromMatrix(int(&g)[size][size]) {
	node ** list = new node * [size];
	for (int i = 0; i < size; i++) {
		list[i] = NULL;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (g[i][j] == 1) {
				node * n = new node{ j, NULL };
				n->next = list[i];
				list[i] = n;
			}
		}
	}
	return list;
}

void printGraphList(node ** list, int size) {
	for (int i=0; i < size; i++) {
		node * tmp = list[i];
		cout << i << ": ";
		while (tmp != NULL) {
			cout << tmp->v << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}
}

void BFSOnList(node ** g, int vertex, int size, void(*action)(int)) {
	queue< int > Q;
	bool * visited = new bool[size];
	int * parent = new int[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
		parent[i] = -1;
	}
	visited[vertex] = true;
	Q.push(vertex);
	action(vertex);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		node * list = g[u];
		while (list != NULL) {
			if (!visited[list->v]) {
				visited[list->v] = true;
				parent[list->v] = u;
				action(list->v);
				Q.push(list->v);
			}
			list = list->next;
		}
	}
	

}

int main() {
	// test 
	BFS(graph, 0, printVertex);
	cout << endl;

	graphList = makeListFromMatrix(graph);
	printGraphList(graphList, V_SIZE);
	BFSOnList(graphList, 0, V_SIZE, printVertex);

	system("pause");
	return 0;
}