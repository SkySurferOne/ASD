#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
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

// =============================================
// Cormen

// wersja oryginalna alg. podzia³u
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

// losuje pivot
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

// =============================================
// Z wyk³adów 

// alg. Hoare'a
int partition2(int A[], int p, int r) {
	int x = A[r];
	int i = p - 1;
	int j;
	for (j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[r], A[i + 1]);
	return i + 1;
}

void quicksort_wykl(int A[], int p, int r) {
	if (p < r) {
		int q = partition2(A, p, r);
		quicksort_wykl(A, p, q - 1);
		quicksort_wykl(A, q + 1, r);
	}
}

// =============================================
// derekursywacja qs (z æwiczeñ)
void qsort_stack(int tab[], int N) {
	stack < int > Q;
	Q.push(0);
	Q.push(N - 1);
	while (!Q.empty()) {
		int r = Q.top(); Q.pop();
		int l = Q.top(); Q.pop();
		int i = partition(tab, l, r);
		if (l < i) {
			Q.push(l);
			Q.push(i);
		}
		if (i + 1 < r) {
			Q.push(i + 1);
			Q.push(r);
		}
	}
}

// TODO
// Jak zmodyfikowaæ qs aby jego z³o¿onoœæ nidy nie sta³a siê O(n^2)
// bez uzycia funkcji random?

int main() {
	srand(time(NULL));
	int n;
	cout << "Podaj n: ";
	cin >> n;
	int * tab = r(n);
	show(tab, n);
	quicksort_corm(tab, 0, n - 1);
	show(tab, n);

	//
	cout << endl;
	int * tab2 = r(n);
	show(tab2, n);
	quicksort_wykl(tab2, 0, n - 1);
	show(tab2, n);

	//
	cout << endl;
	int * tab3 = r(n);
	show(tab3, n);
	qsort_stack(tab3, n);
	show(tab3, n);

	system("pause");
	return 0;
}