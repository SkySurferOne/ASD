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

void przywroc(int T[], int k, int n) {
	int i, j;
	i = T[k - 1]; // wartoœæ pod wierzcho³kiem

	while (k <= n / 2) {
		j = 2 * k;
		if ((j < n) && (T[j - 1] < T[j])) j++;
		if (i >= T[j - 1])
			break;
		else {
			T[k - 1] = T[j - 1];
			k = j;
		}
	}
	T[k - 1] = i;
}

// sortowanie tablicy
void heapsort(int T[], int n) {
	int k, swap;
	for (k = n / 2; k > 0; k--) przywroc(T, k, n);
	do {
		swap = T[0];
		T[0] = T[n - 1];
		T[n - 1] = swap;
		n--;
		przywroc(T, 1, n);
	} while (n > 1);
}

// cormen style
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return (i - 1) / 2; }

// naprawia kopiec o rozm. hs od wierzcho³ka i
void heapify(int A[], int i, int hs) {
	int l = left(i);
	int r = right(i);
	int largest = 0;

	if (l < hs && A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r < hs && A[r] > A[largest])
		largest = r;
	if (largest != i) {
		swap(A[i], A[largest]);
		heapify(A, largest, hs);
	}
}

// formuje kopiec
void build_heap(int A[], int n) {
	for (int i = n / 2; i >= 0; i--)
		heapify(A, i, n);
}

// funkcja sortuj¹ca
void heapsort_c(int A[], int n) {
	build_heap(A, n);
	for (int i = n-1; i >= 1; i--) {
		swap(A[0], A[i]);
		heapify(A, 0, i);
	}
}

int main() {
	srand(time(NULL));
	int n;
	cout << "Podaj n: ";
	cin >> n;
	int * T = r(n);
	show(T, n);
	heapsort(T, n);
	show(T, n);

	int * T2 = r(n);
	show(T2, n);
	heapsort_c(T2, n);
	show(T2, n);

	system("pause");
	return 0;
}