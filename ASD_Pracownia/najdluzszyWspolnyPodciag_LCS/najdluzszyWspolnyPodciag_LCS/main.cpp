#include <iostream>
#include <algorithm> 
using namespace std;

/*
	f(i, j) returns length of LCS (longest common subseqence)
	A[0...i]
	B[0...j]

			  
	          | max{ f(i, j), f(i, j-1) } gdy A[i] != B[j]
	f(i, j) = |
			  |	f(i-1, j-1)+1 gdy A[i] = B[j]
			  
*/
int LCS(int A[], int B[], int  n, const int  m) {
	int ** f = new int *[n+1];
	for (int i = 0; i < n + 1; i++)
		f[i] = new int[m + 1];

	for (int i = 0; i < n + 1; i++)
		f[i][0] = 0;

	for (int i = 0; i < m + 1; i++)
		f[0][i] = 0;

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (A[i] != B[j]) 
				f[i][j] = max(f[i-1][j], f[i][j-1]);
			else 
				f[i][j] = f[i-1][j-1] + 1;
		}
	}

	return f[n][m];
}

int LIS(int A[], int n) {
	int * B = new int[n];
	for (int i = 0; i < n; i++)
		B[i] = A[i];
	sort(B, B + n);

	int result = LCS(A, B, n, n);
	delete[] B;

	return result;
}

//
void print(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

int main() {
	int A[] = { 1, 2, 3, 4, 5, 6 };
	int B[] = { 1, 4, 2, 3, 5 };
	int n = sizeof(A) / sizeof(int);
	int m = sizeof(B) / sizeof(int);

	cout << "A: "; print(A, n);
	cout << "B: "; print(B, m);
	cout << "LCS: " << LCS(A, B, n, m) << endl;
	cout << "LIS in B: " << LIS(B, m) << endl;

	system("pause");
	return 0;
}