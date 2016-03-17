#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

// A powinna zawieraæ liczby naturalne z zakresu [0, k-1]
// k < n
void CountingSort(int A[], int n, int k) {
	int * B = new int[n];
	int * C = new int[k];
	for(int i = 0; i < k; i++) C[i] = 0;
	for (int i = 0; i < n; i++)
		C[A[i]]++; // zlicza iloœæ liczb w A
	for (int i = 1; i < k; i++)
		C[i] = C[i] + C[i - 1]; // zlicza ile innych cyfr jest przed i-t¹
	for (int i = n - 1; i >= 0; i--) {
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--;
	}
	for (int i = 0; i < n; i++)
		A[i] = B[i];
	delete[] C;
	delete[] B;
}

int * r(int n, int k) {
	int * tab = new int[n];
	for (int i = 0; i < n; i++)
		tab[i] = rand() % k;
	return tab;
}

void show(int A[], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {
	int n, k, * A;
	cout << "Podaj n i k: " << endl;
	cin >> n >> k;
	A = r(n, k);
	show(A, n);
	CountingSort(A, n, k);
	show(A, n);

	system("pause");
	return 0;
}