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

// Cormen
int partition(int A[], int p, int r) {
	int x = A[p];
	int i = p - 1;
	int j = r + 1;
	while (true) {
		do j--;
		while (A[j] > x);
		do i++;
		while (A[i] < x);
		if (i < j)
			swap(A[i], A[j]);
		else
			return j;
	}
}

int partition_rand(int A[], int p, int r) {
	int q = (rand() % (r - p + 1)) + p;
	swap(A[p], A[q]);
	return partition(A, p, r);
}

void quicksort_corm(int A[], int p, int r) {
	if (p < r) {
		int q = partition_rand(A, p, r);
		quicksort_corm(A, p, q);
		quicksort_corm(A, q + 1, r);
	}
}

int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	int * tab = r(n);
	show(tab, n);
	quicksort_corm(tab, 0, n - 1);
	show(tab, n);

	system("pause");
	return 0;
}