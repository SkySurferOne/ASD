#include <iostream>
#include <queue>
using namespace std;
#define V_SIZE 6

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
   // 0  1  2  3  4  5
	{ 0, 0, 0, 1, 1, 1 },
	{ 0, 0, 0, 1, 1, 1 },
	{ 0, 0, 0, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0 }
};

struct vertex {
	int color; // 0 - niepokolorowany
	int * to;
	int edges;
};

vertex * makeTable(int g[][V_SIZE]) {
	vertex * nV = new vertex[V_SIZE];
	for (int i = 0; i < V_SIZE; i++) {
		
		int c = 0;
		for (int j = 0; j < V_SIZE; j++)
			if (graph[i][j]) c++;

		nV[i].to = new int[c];
		nV[i].edges = c;

		int k = 0;
		for (int j = 0; j < V_SIZE; j++)
			if (graph[i][j]) nV[i].to[k++] = j;
	}

	return nV;
}

bool dwudzielny(vertex * V, int n) {
	queue< int > Q;
	Q.push(0);
	V[0].color = 1;

	for (int i = 1; i < n; i++)
		V[i].color = 0;

	while (!Q.empty()) {
		int current = Q.front(); Q.pop();
		
		for (int i = 0; i < V[current].edges; i++) {
			int j = V[current].to[i];
			int color = 3 - V[current].color;

			if (V[j].color == 0) {
				V[i].color = color;
				Q.push(j);
			} else if (V[j].color != color){
				return false;
			}
		}
	}

	return true;
}

int main() {
	(dwudzielny(makeTable(graph), V_SIZE)) ? cout << "Graf jest dwudzielny" : cout <<"Graf nie jest dwudzielny";
	cout << endl;

	system("pause");
	return 0;
}