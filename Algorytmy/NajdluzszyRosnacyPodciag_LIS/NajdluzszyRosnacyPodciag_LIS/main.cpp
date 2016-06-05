#include <iostream>
using namespace std;

void printSolution(int A[], int P[], int i) {
	if (i != -1) {
		printSolution(A, P, P[i]);
		cout << A[i] << " ";
	}
}

int lis(int A[], int n) {
	int * F = new int [n];
	int * P = new int [n];
	int max = 0;
	F[0] = 1;
	P[0] = -1; // tablica poprzedników

	for (int i = 1; i < n; i++) {
		F[i] = 1; 
		P[i] = -1;
		for (int j = 0; j < i; j++) {
			if (A[j] < A[i] && F[j] + 1 > F[i]) {
				F[i] = F[j] + 1;
				P[i] = j;
			}
		}
		if (F[max] < F[i]) max = i;
		
	}


	printSolution(A, P, max);
	cout << endl;
	int c = F[max];
	
	delete[] F;
	delete[] P;

	return c;
}

int main() {
	int A[] = { 0, 5, 1 };
	int n = sizeof(A) / sizeof(int);
	cout << lis(A, n) << endl;
	system("pause");
	return 0;
}