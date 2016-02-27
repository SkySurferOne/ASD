#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int * r(int n) {
	int * t = new int[n]; 
	for(int i=0; i<n; i++)
		t[i] = rand() % 50;
	return t; 
}

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

void bsort(int t[], int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n-1-i; j++) {
			if(t[j]>t[j+1]) {
				int tmp = t[j];
				t[j] = t[j+1];
				t[j+1] = tmp; 
			}
		}

	}
}

int main() {
	srand(time(NULL));
	int n;
	cout << "Podaj n: ";
	cin >> n;
	int * tab = r(n);
	show(tab, n);
	bsort(tab, n);
	show(tab, n);
	return 0;
}