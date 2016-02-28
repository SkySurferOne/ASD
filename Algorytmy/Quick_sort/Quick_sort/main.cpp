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

void quicksort(int d[], int l, int r) {
	int i = (l + r)/2;
	int pivot = d[i];
	d[i] = d[r];
	int j = l;
	for (int i = l; i < r; i++) {
		if (d[i] < pivot) {
			int tmp = d[j];
			d[j] = d[i];
			d[i] = tmp;
			j++;
 		}
	}
	d[r] = d[j];
	d[j] = pivot;
	if (l < j - 1) quicksort(d, l, j - 1);
	if (j + 1 < r) quicksort(d, j + 1, r);
}

int main() {
	int n;
	cin >> n;
	int * tab = r(n);
	show(tab, n);
	quicksort(tab, 0, n - 1);
	show(tab, n);

	system("pause");
	return 0;
}