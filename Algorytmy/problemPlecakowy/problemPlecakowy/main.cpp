#include <iostream>
#include <algorithm>
using namespace std;

/*
	f: NxN->N - maksymalna wartoœæ przedmiotów
	p1 ... pn

	f(0, m) = 0 (m>=0)
	f(i, 0) = 0 (i>=0)

			  |  f(i-1, m) gdzie wi > m
	f(i, m) = |
			  |  max{ f(i-1, m), f(i-1, m-w(pi)) + c(pi)}
*/
int backpack(int W[], int C[], int n, int m) {
	n++; m++;
	int ** f = new int * [n];
	for (int i = 0; i < n; i++)
		f[i] = new int[m];

	for (int i = 0; i < n; i++)
		f[i][0] = 0;
	for (int i = 0; i < m; i++)
		f[0][i] = 0;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (W[i] > j)
				f[i][j] = f[i - 1][j];
			else {
				int w = j - W[i-1];
				if (w < 0) w = 0;
				f[i][j] = max(f[i - 1][j], f[i-1][w] + C[i-1]);
			}
		}
	}

	return f[n-1][m-1];
}

int main() {
	int W[] = { 1, 2, 1, 5, 5 };
	int C[] = { 20, 20, 22, 6, 5 };
	int n = 5;
	int m = 10;
	cout << backpack(W, C, n, m) << endl;

	system("pause");
	return 0;
}