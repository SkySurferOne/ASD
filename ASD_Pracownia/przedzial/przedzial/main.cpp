#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void show(int tab[], int n) {
	for (int i = 0; i < n; i++)
		cout << tab[i] << " ";
	cout << endl;
}

int * random(int n) {
	int * tab = new int[n];
	for (int i = 0; i < n; i++)
		tab[i] = rand() % 50;
	return tab;
}

// O(n)
int range1(int tab[], int a, int b, int n) {
	if (b > n) return -1;
	int sum = 0;
	for (int i = a; i <= b; i++)
		sum += tab[i];
	return sum;
}

// zwraca tablicê sum prefiksowych
int * dopreftab(int tab[], int n) {
	int sum = 0;
	int * ptab = new int[n];
	for (int i = 0; i < n; i++) {
		sum += tab[i];
		ptab[i] = sum;
	}
	return ptab;
}

// O(1)
int range2(int tab[], int a, int b, int n) {
	if (b > n || a > b || a < 0) return -1;
	return (a == 0) ? tab[b] : tab[b] - tab[a - 1];
}

int * maketree(int tab[], int n) { // n musi byæ parzyste
	if (n % 2 != 0 && (n/2) % 2 != 0) return NULL;
	int * tree = new int[2*n - 1];

	//for (int i = 0; i < 2*n-1; i++) {
	//	tree[i] = 0;
	//}

	for (int i = n - 1; i >= 0; i -= 2) {
		//cout << n - 1 + i << " " << tab[i] << " " << tab[i - 1] << endl;
		tree[n - 1 + i] = tab[i];
		tree[n - 1 + i - 1] = tab[i - 1];
		tree[(n - 2 + i) / 2] = tab[i] + tab[i - 1];
	}

	//show(tree, 2 * n - 1);

	for (int i = n - 2; i > 0; i-=2) {
		tree[(i-1)/2] = tree[i] + tree[i - 1];
	}

	return tree;
}

// Wypisuje wszystkie wêz³y na œcie¿ce liœæ - korzeñ
void toRoot(int tab[], int n, int leaf) {
	if (leaf >= 0 && leaf < n) {
		int v = n - 1 + leaf;
		//cout << tab[leaf] << endl;
		while (v != 0) {
			cout << tab[v] << endl;
			v = (v - 1) / 2;
		}
		cout << tab[0] << endl;
	}
}

// O(logn) - zwraca wynik sumy przedzia³u [a,b] na podstawie drzewa przedzia³owego
int range3(int tab[], int a, int b, int n) {
	int va = n - 1 + a; int vb = n - 1 + b;
	
	// skrajne przedzia³y rozk³adu
	int res = tab[va];
	
	if (va != vb) res += tab[vb];
	//cout << "va: "<< va << " vb: " << vb << " res: " << res << endl;
	// spacer a¿ do momentu spotkania
	while (((va - 1) / 2) != ((vb - 1) / 2)) {
		
		if (va % 2 == 1) res += tab[va + 1];
		//cout << "va: " << va << " vb: " << vb << " res: " << res << endl;
		if (vb % 2 == 0) res += tab[vb - 1];
		//cout << "va: " << va << " vb: " << vb << " res: " << res << endl;
		va = (va - 1) / 2; vb = (vb - 1) / 2;
	}
	return res;
}

int main() {
	srand(time(NULL));
	int n, a, b;
	
	cout << "n, a, b:" << endl;
	cin >> n >> a >> b;
	int * tab = random(n);
	int * preftab = dopreftab(tab, n);

	show(tab, n);
	/*show(preftab, n);*/
	cout << range1(tab, a, b, n) << endl;
	cout << range2(preftab, a, b, n) << endl;

	int * tree = maketree(tab, n);
	show(tree, 2 * n - 1);
	/*cout << "leaf number: " << endl;
	int leaf;
	cin >> leaf;
	toRoot(tree, n, leaf);*/
	//int test[15] = { 36, 10, 26, 3, 7, 11, 15, 1, 2, 3, 4, 5, 6, 7, 8 };
	cout << range3(tree, a, b, n) << endl;

	delete[] tab;
	delete[] preftab;
	system("pause");
	return 0;
}