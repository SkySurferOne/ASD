#include <iostream>
using namespace std;

#define V_SIZE 5

// reprezentacja macierzowa 
int graph[][V_SIZE] = {
	// 0  1  2  3  4
	{ 0, 5, 4, 8, 0 }, // 0
	{ -4, 0, -2, 0, 5 }, // 1
	{ 0, 0, 0, 5, 2 }, // 2
	{ -1, 2, 0, 0, -1 }, // 3
	{ 0, 0, 4, 2, 0 } // 4
};

int d[V_SIZE][V_SIZE];

void floydWarshall(int g[][V_SIZE]) {
	for (int i = 0; i < V_SIZE; i++) {
		for (int j = 0; j < V_SIZE; j++) {
			if (i == j)
				d[i][j] = 0;
			else if (g[i][j] != 0)
				d[i][j] = g[i][j];
			else
				d[i][j] = INT16_MAX;
		}
	}
			
	for (int k = 0; k < V_SIZE; k++) {
		for (int i = 0; i < V_SIZE; i++) {
			for (int j = 0; j < V_SIZE; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

}

void print(int d[V_SIZE][V_SIZE]) {
	for (int i = 0; i < V_SIZE; i++)
		for (int j = 0; j < V_SIZE; j++) {
			cout << "d[" << i << "]" << "[" << j << "] = ";
			if (d[i][j] == INT16_MAX)
				cout << "NO PATH";
			else
				cout << d[i][j];
			cout << endl;
		}
}

int main() {
	floydWarshall(graph);
	print(d);

	system("pause");
	return 0;
}