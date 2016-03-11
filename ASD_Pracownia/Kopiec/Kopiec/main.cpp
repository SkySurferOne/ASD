#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 15;

struct heap {
	int A[MAX_SIZE];
	int size;
};

//
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }
int parent(int i) { return ((i - 1) / 1); }

// naprawia kopiec
void heapify(heap * H, int i) {
	int ind_max = i;

	if (left(i) < H->size && H->A[left(i)] > H->A[ind_max])
		ind_max = left(i);
	if (right(i) < H->size && H->A[right(i)] > H->A[ind_max])
		ind_max = right(i);
	if (ind_max != i) {
		swap(H->A[i], H->A[ind_max]);
		heapify(H, ind_max);
	}
}

// formuje kopiec
void build_heap(heap * H) {
	for (int i = parent(H->size -1); i >= 0; i--)
		heapify(H, i);
}

// Wstawia pod konkretny wêze³ (musi byæ z przedzia³u 0 do MAX_SIZE-1) wiêkszy klucz i naprawia kopiec (jeœli to koneczne)
void increase_key(heap * H, int key, int i) {
	if (H->A[i] >= key) {
		cout << "Klucz w wezle jest mniejszy lub rowny" << endl;
		return ;
	}
	if (i == 0 || H->A[parent(i)] >= key) {
		H->A[i] = key;
	} else {
		H->A[i] = H->A[parent(i)];
		increase_key(H, key, parent(i));
	}
}

// analogicznie 
void decrease_key(heap * H, int key, int i) {
	if (H->A[i] <= key) {
		cout << "Klucz w wezle jest wiekszy lub rowny" << endl;
		return;
	}
	H->A[i] = key;
	heapify(H, i);
}

// wstawia nowy klucz do kopca (pod warunkiem, ze H->size < MAX_SIZE)
void insert(heap * H, int key) {
	if (H->size+1 == MAX_SIZE) return;
	H->A[H->size] = INT_MIN;
	H->size++;
	increase_key(H, key, H->size);
}

// usuwa noda z kopca
void delete_node(heap * H, int i) {
	if (H->size == 0) return;
	increase_key(H, INT_MAX, i);
	swap(H->A[0], H->A[H->size - 1]);
	H->size--;
	heapify(H, i);
}

// TODO
// heapify dla min heap
// usuwanie min, max i dodawianie el. w czasie logn na dwóch kopcach

// funkcje pomocnicze
void r(heap * H, int n) {
	for (int i = 0; i<n; i++)
		H->A[i] = rand() % 50;
}

int dig(long long int n) {
	return (n == 0) ? 1 : ceil(log10(abs(n) + 1));
}

void show(int tab[], int n, bool ind = false) {
	if (n == 0) { cout << "-"; return; }
	if (ind) {
		int jmp;
		for (int i = 0; i < n; i++) {
			cout << i;
			jmp = (dig(tab[i]) > dig(i)) ? dig(tab[i]) : 1;
			while (jmp-->0 && i != n - 1) cout << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++) {
		cout << tab[i];
		if (ind && dig(i) > dig(tab[i])) {
			int jmp = dig(i);
			while (jmp-- > 0 && i != n - 1) cout << " ";
		}
		else cout << " ";
	}

	cout << endl;
}

void scan_n(int &n) {
	int f;
	cout << "Podaj n: ";
	do {
		f = scanf_s("%d", &n);
		if (!f) exit(1);
		if (n > MAX_SIZE || n < 1) cout << "Zla wartosc. Podaj jeszcze raz: ";
	} while (n > MAX_SIZE || n < 1);
}

void scan_ind(int &n) {
	int f;
	cout << "Podaj ind wezla: ";
	do { 
		f = scanf_s("%d", &n);
		if (!f) exit(1);	
		if(n >= MAX_SIZE || n < 0) cout << "Zla wartosc. Podaj jeszcze raz: ";
	} while (n >= MAX_SIZE || n < 0);
		
}

void fanShow(string label) {
	string str = "\n//////////////////////////////////////////////////\n                  " +
				 label + "                 \n" +
				 "//////////////////////////////////////////////////\n\n";
	printf_s(str.c_str());
}

void test(heap * H) {
	int n;
	scan_n(n);
	r(H, n);
	H->size = n;
	show(H->A, H->size, true);
	cout << endl;
	show(H->A, MAX_SIZE, true);

	fanShow("build_heap");
	build_heap(H);
	show(H->A, H->size, true);
	//cout << endl;
	//show(H->A, MAX_SIZE, true);

	int opt;
	cout << endl << "Podaj opt: ";
	while (scanf_s("%d", &opt)) {
		int key, i;
		switch (opt)
		{
			case 0:
				fanShow("increase_key");
				scan_ind(i);
				cout << "Podaj klucz: "; cin >> key;
				increase_key(H, key, i);
				break;
			case 1:
				fanShow("decrease_key");
				scan_ind(i);
				cout << "Podaj klucz: "; cin >> key;
				decrease_key(H, key, i);
				break;
			case 2:
				fanShow("insert");
				cout << "Podaj klucz: "; cin >> key;
				insert(H, key);
				break;
			case 3:
				fanShow("delete_node");
				scan_ind(i);
				delete_node(H, i);
				break;
			default:
				printf_s("\n 0 - incr key \n 1 - decr key \n 2 - insert key \n 3 - usun wezel z kopca\n dow litera - wyjdz\n\nPodaj opt: ");
				continue;
		}
		cout << endl;
		show(H->A, H->size, true);
		//cout << endl;
		//show(H->A, MAX_SIZE, true);
		cout << endl << "Podaj opt: ";
	} 
}

int main() {
	struct heap * H = new heap;
	test(H);

	system("pause");
	return 0;
}