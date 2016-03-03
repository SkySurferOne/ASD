#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int * r(int n) {
	int * t = new int[n];
	for (int i = 0; i<n; i++)
		t[i] = rand() % 50;
	return t;
}

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

void minmax(int  t[], int n, int &min, int &max) {
    min = 1e3;
	max = -1e3;
	int i, j;
	i = 0;
	j = n - 1;
	do {
		if (t[i] < t[j]) {
			if (t[i] < min) min = t[i];
			if (t[j] > max) max = t[j];
		} else {
			if (t[j] < min) min = t[j];
			if (t[i] > max) max = t[i];
		}
		i++;
		j--;
	} while (i < j);

}
int main() {
	int * tab = r(10);
	show(tab, 10);
	int min, max;
	minmax(tab, 10, min, max);
	cout << min << " " << max << endl;

	system("pause");
	return 0;
}