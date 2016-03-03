#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Typ wêz³ów drzewa
struct BTNode {
	BTNode * left;
	BTNode * right;
	int value;
};

// Tworzenie struktury drzewa 
/*
	    0
	   / \
	  1   2
	 / \ / \
	3  4 5  6
   /\  / /
  7 8 9  10
*/

BTNode G = { NULL, NULL, 6 };
BTNode H = { NULL, NULL, 7 };
BTNode I = { NULL, NULL, 8 };
BTNode J = { NULL, NULL, 9 };
BTNode K = { NULL, NULL, 10 };

BTNode D = { &H, &I, 3 };
BTNode E = { &J, NULL, 4 };
BTNode F = { &K, NULL, 5 };
BTNode B = { &D, &E, 1 };
BTNode C = { &F, &G, 2 };

BTNode A = { &B, &C, 0 };

/*
	Przechodzenie drzewa binarnego - algorytm DFS
*/

// DFS: pre-order
void preorder(BTNode * v) {
	if (v != NULL) {
		cout << v->value << " ";
		preorder(v->left);
		preorder(v->right);
	}
}

// DFS: pre-order - algorytm stosowy
void preorderStack(BTNode * v) {
	stack < BTNode * > stos;
	stos.push(v);

	while (!stos.empty()) {
		v = stos.top();
		stos.pop();
		cout << v->value << " ";
		if (v->right != NULL)
			stos.push(v->right);
		if (v->left != NULL)
			stos.push(v->left);
	}
	cout << endl;
}

// DFS: in-order 
void inorder(BTNode * v) {
	if (v != NULL) {
		inorder(v->left);
		cout << v->value << " ";
		inorder(v->right);
	}
}

// DFS: in-order - algorytm stosowy
void inorderStack(BTNode * v) {
	stack < BTNode * > stos;
	BTNode * cp = v;

	while (!stos.empty() || cp != NULL) {
		if (cp != NULL) {
			stos.push(cp);
			cp = cp->left;
		} else {
			cp = stos.top();
			stos.pop();
			cout << cp->value << " ";
			cp = cp->right;
		}
	}
	cout << endl;
}

// DFS: post-order
void postorder(BTNode * v) {
	if (v != NULL) {
		postorder(v->left);
		postorder(v->right);
		cout << v->value << " ";
	}
}

// DFS: post-order - algorytm stosowy
void postorderStack(BTNode * v) {
	stack < BTNode * > stos;
	BTNode * pp, * cp;
	stos.push(v);
	pp = NULL;

	while (!stos.empty()) {
		cp = stos.top();

		if (pp == NULL || (pp->left == cp || pp->right == cp)) {
			if (cp->left != NULL)
				stos.push(cp->left);
			else if (cp->right != NULL)
				stos.push(cp->right);

		} else if (cp->left == pp) {
			if (cp->right != NULL)
				stos.push(cp->right);
		} else {
			cout << cp->value << " ";
			stos.pop();
		}
		pp = cp;
	}
	cout << endl;
}

/*
	Algorytm kolejkowy BFS
*/

void bfs(BTNode * v) {
	queue < BTNode * > kolejka;
	kolejka.push(v);

	while (!kolejka.empty()) {
		v = kolejka.front();
		kolejka.pop();

		cout << v->value << " ";
		if (v->left != NULL) 
			kolejka.push(v->left);
		if (v->right != NULL)
			kolejka.push(v->right);
	}
	cout << endl;
}

// Zwraca wysokoœæ drzewa
void getHeight(BTNode * v, int &h, int cur = 0) {
	if (v != NULL) {
		cur++;
		getHeight(v->left, h, cur);
		getHeight(v->right, h, cur);
	} else {
		if (cur > h)
			h = cur;
	}
}

// Podaje iloœæ wêz³ów na ka¿dym poziomie
void leafcountRec(BTNode * v, int * tab, int cur = 0) {
	if (v != NULL) {
		tab[cur++]++;
		leafcountRec(v->left, tab, cur);
		leafcountRec(v->right, tab, cur);
	}
}

int * leafcount(BTNode * v, int lv) {
	int * tab = new int[lv];
	for (int i = 0; i < lv; i++)
		tab[i] = 0;

	leafcountRec(v, tab);
	return tab;
}

// Generuje drzewo 
BTNode * genBNTree() {
	int n;
	cin >> n;
	if (n <= 0) return NULL;

	BTNode ** tab = new BTNode * [n];
	for (int i = 0; i < n; i++)
    	tab[i] = new BTNode;;

	int ic = 1;
	for (int i = 0; i < n; i++) {
		int w, l, p;
		cout << "Podaj: wartosc wezla ["<< i <<"], 0/1 lewe dziecko, 0/1 prawe dziecko:" << endl;
		cin >> w >> l >> p;
		
		tab[i]->value = w;
		tab[i]->left = (l!=0 && ic<n) ? tab[ic++] : NULL;
		tab[i]->right = (p!=0 && ic<n) ? tab[ic++] : NULL;
	}
	BTNode * v = tab[0];
	delete[] tab;
	return v;
}

int main() {

	/*
		Przegl¹danie drzewa binarnego
	*/

	preorder(&A);
	cout << endl;
	preorderStack(&A);

	inorder(&A);
	cout << endl;
	inorderStack(&A);

	postorder(&A);
	cout << endl;
	postorderStack(&A);

	bfs(&A);

	/*
		Inne problemy
	*/

	// wysokoœæ drzewa
	int h = -1;
	getHeight(&A, h);
	cout << h << endl;

	// Iloœæ wêz³ów na ka¿dym poziomie
	int * tab = leafcount(&A, h);
	for (int i=0; i < h; i++)
		cout << i << ": " << tab[i] << endl;

	// Generuj drzewo 
	BTNode * tree = genBNTree();
	bfs(tree);

	system("pause");
	return 0;
}