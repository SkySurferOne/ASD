#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
using namespace std;

// O(n^3)
int ssp1(int A[], int n) {
	int part, res;
	part = res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			part = 0;
			for (int k = i; k <= j; k++) part += A[k];
			if (part > res) res = part;
		}
	}
	return res;
}

// O(n^2)
int ssp2(int A[], int n) {
	int part, res;
	part = res = 0;
	for (int i = 0; i < n; i++) {
		part = 0;
		for (int j = i; j < n; j++) {
			part += A[j];
			if (part > res) res = part;
		}
	}
	return res;
}

// O(nlogn)
int ssp3(int A[], int n) {
	if (n == 0) return 0;
	if (n == 1) return max(0, A[0]);

	int k = n / 2;
	int L = ssp3(A, k);
	int R = ssp3(A + k, n - k);

	int spanL, spanR, par;
	spanL = spanR = par = 0;
	for (int i = k; i < n; i++) {
		par += A[i];
		if (par > spanR) spanR = par;
	}
	par = 0;
	for (int i = k - 1; i >= 0; i--) {
		par += A[i];
		if (par > spanL) spanL = par;
	}

	return max(max(L, R), spanL + spanR);
}

// O(n)
int ssp4(int A[], int n) {
	int part, res;
	part = res = 0;
	for (int i = 0; i < n; i++) {
		part += A[i];
		if (part < 0) part = 0;
		if (part > res) res = part;
	}
	return res;
}

int * random(int n) {
	int * tab = new int [n];
	for (int i = 0; i < n; i++)
		tab[i] = (rand() % 201) - 100;
	return tab;
}

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}
int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	int * tab  = random(n);
	show(tab, n);
	cout << ssp1(tab, n) << endl;
	cout << ssp2(tab, n) << endl;
	cout << ssp3(tab, n) << endl;
	cout << ssp4(tab, n) << endl;

	system("pause");
	return 0;
}