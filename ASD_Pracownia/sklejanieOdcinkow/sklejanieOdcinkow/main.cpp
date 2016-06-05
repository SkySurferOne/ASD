#include <iostream>
#include <queue>
using namespace std;

struct line {
	int a, b;
};

bool canIGoThere(int ** g, unsigned int n, unsigned int beg, unsigned int end) {
	bool * visited = new bool[n];
	for (unsigned int i = 0; i < n; i++)
		visited[i] = false;
	if (beg >= n || end >= n) return false;
	visited[beg] = true;
	queue< unsigned int > Q;
	Q.push(beg);

	while (!Q.empty()) {
		int u = Q.front(); Q.pop();

		for (unsigned int i = 0; i < n; i++) {
			if (g[u][i] && !visited[i]) {
				visited[i] = true;
				if (end == i) return true;
				Q.push(i);
			}
		}

	}

	delete[] visited;
	return false;
}

int main() {
	unsigned int n, beg, end;
	
	cout << "Podaj ilosc krawedzi: "; cin >> n;
	line * L = new line[n];

	// a, b >= 0, zak³adam poprawnoœæ wpisywanych danych
	for (int i = 0; i < n; i++) {
		cout << "Podaj a i b dla krawedzi nr [" << i << "]: ";
		cin >> L[i].a >> L[i].b;
	}

	// beg < end
	cout << "Podaj poczatek  i koniec drogi: "; cin >> beg >> end;
	int max = -1; 
	for (int i = 0; i < n; i++)
		if (L[i].b > max)
			max = L[i].b;

	//
	max++;
	int ** graph = new int *[max];
	for (int i = 0; i < max; i++)
		graph[i] = new int[max];

	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
			graph[i][j] = 0;

	for (int i = 0; i < n; i++)
		graph[L[i].a][L[i].b] = 1;

	// mamy gotowy graf stworzony na podstawie tablicy krawêdzi, teraz mo¿emy sprawdziæ czy dojdziemy z beg do end
	(canIGoThere(graph, max, beg, end)) ? cout << "Mozna tam dojsc" : cout << "Nie mozna tam dojsc";
	cout << endl;

	system("pause");
	return 0;
}
