#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
	Mamy tablicê A n-elementow¹, zawieraj¹c¹ elementy z przedzia³u [0, n^2-1]. Nale¿y j¹ posortowaæ.

	Rozwi¹zanie:

	System n-kowy
	Liczby z zakresu: [0, n^2-1] 
	mo¿na zapisaæ w postaci: An + B, gdzie A, B nale¿¹ do przedzia³u [0, n-1]

	Nale¿y posortowaæ pozycyjnie z u¿yciem sortowania przez zliczanie.
	Czas sortowania: O(n)
*/

#define N 10
#define P 2

// zwraca cyfrê o pozycji 1...numlen(num) licz¹c od ty³u
int getNumByPos(int num, int base, int pos) {
	if (pos == 1) return num%base;
	int i = 1;
	num /= base;
	int dig = 0;
	while (num != 0 && i != pos) {
		dig = num%base;
		num /= base;
		i++;
	}
	return dig;
}

// sortuje wzglêdem pozycji p
void posSort(int A[], int n, int p) {
	int * res = new int[n];
	int * tab = new int[n];

	for (int i = 0; i < n; i++)
		tab[i] = 0;

	for (int i = 0; i < n; i++)
		tab[getNumByPos(A[i], n, p)]++;

	for (int i = 1; i < n; i++)
		tab[i] = tab[i] + tab[i - 1];

	for (int i = n - 1; i >= 0; i--)
		res[--tab[getNumByPos(A[i], n, p)]] = A[i];

	for (int i = 0; i < n; i++)
		A[i] = res[i];

	delete[] res;
	delete[] tab;
}

// Sortuje n elementow¹ tablicê z elementami z zakresu [0, n^p-1]
void sort(int A [], int n, int p) {
	for (int i = 1; i <= p; i++) 
		posSort(A, n, i);
}

void fillTable(int A[], int n, int p) {
	int max = pow(n, p);
	for (int i = 0; i < n; i++) 
		A[i] = rand() % max;
}

void show(int A [], int n) {
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {
	srand(time(NULL));
	int A[N];
	fillTable(A, N, P);
	show(A, N);

	sort(A, N, P);
	show(A, N);

	system("pause");
	return 0;
}