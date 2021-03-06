#include <iostream>
using namespace std;

struct BSTNode {
	BSTNode * up;
	BSTNode * left;
	BSTNode * right;
	int key, 
		sum; // suma w�z��w w lewym poddrzewie
};

// wy�wietla drzewo (niemalej�co wg warto�ci key)
void inorder(BSTNode * v) {
	if (v != NULL) {
		inorder(v->left);
		cout << v->key << " ";
		inorder(v->right);
	}
}

// dodaje w�ze� do drzewa
bool addNode(BSTNode * &tree, int key) {
	if (tree == NULL) {
		tree = new BSTNode;
		if (tree == NULL) return false;
		tree->key = key;
		tree->left = NULL;
		tree->right = NULL;
		tree->up = NULL;
		tree->sum = 0;
		return true;
	} else {
		bool run = true;
		BSTNode * cp = tree;
		while (run) {
			if (key <= cp->key) {
				cp->sum++;
				if (cp->left == NULL) {
					run = false;
				} else {
					cp = cp->left;
				}
			} else {
				if (cp->right == NULL) 
					run = false;
				else
					cp = cp->right;
			}		
		}
		BSTNode * tmp = new BSTNode;
		if (tmp == NULL) return false;
		tmp->key = key;
		tmp->up = cp;
		tmp->left = tmp->right = NULL;
		tmp->sum = 0;
		if (key <= cp->key)
			cp->left = tmp;
		else 
			cp->right = tmp;
		return true;
	}
}

// zwraca w�ze� o kluczu key (o ile istnieje)
BSTNode * isNode(BSTNode * v, int key) {
	while (v != NULL && key != v->key) {
		if (key < v->key) 
				v = v->left;
		 else
				v = v->right;
	}
	return v;
}

// jw tylko rekurencyjnie
BSTNode * find(BSTNode * root, int key) {
	if (root == NULL) return NULL;
	if (root->key == key) return root;
	else if (key < root->key)
		return find(root->left, key);
	else return find(root->right, key);
}

// zwraca min w drzewie
BSTNode * treeMin(BSTNode * root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}

// zwraca max w drzewie
BSTNode * treeMax(BSTNode * root) {
	while (root->right != NULL)
		root = root->right;
	return root;
}

// zwraca nast�pnika
BSTNode * treeSuccessor(BSTNode * v) {
	if (v->right != NULL)
		return treeMin(v->right);

	BSTNode * y = v->up;
	while (y != NULL && v == y->right) {
		v = y;
		y = y->up;
	}
	return y;
}

// zwraca poprzednika
BSTNode * treePredecessor(BSTNode * v) {
	if (v->left != NULL)
		return treeMax(v->left);

	BSTNode * y = v->up;
	while (y != NULL && v == y->left) {
		v = y;
		y = y->up;
	}
	return y;
}

// usuwa w�ze� poczym go zwraca (uwaga nie naprawia sum)
BSTNode * deleteNode(BSTNode * &root, BSTNode * z) {
	BSTNode * y, * x;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else
		y = treeSuccessor(z);
	
	if (y->left != NULL)
		x = y->left;
	else 
		x = y->right;

	if (x != NULL) 
		x->up = y->up;

	if (y->up == NULL)
		root = x;
	else if (y == y->up->left)
		y->up->left = x;
	else
		y->up->right = x;

	if (y != z)
		z->key = y->key;

	return y;
}

// operacja deleteNode mo�e zepsu� dzia�anie tej funkcji
int getNElement(BSTNode * v, int i) {
	if (v == NULL) return -1;
	
	int lsum;
	if (v->left == NULL)
		lsum = 0;
	else
		lsum = v->sum;
	
	if (lsum + 1 == i) 
		return v->key;
	
	if (lsum >= i)
		return getNElement(v->left, i);

	return getNElement(v->right, i - lsum - 1);
}

int main() {
	BSTNode * tree = NULL;
	addNode(tree, 8);
	addNode(tree, 5);
	addNode(tree, 10);
	addNode(tree, 1);
	addNode(tree, 6);
	addNode(tree, 11);
	addNode(tree, 7);
	addNode(tree, 20);

	inorder(tree);
	cout << getNElement(tree, 2) << endl;

	cout << endl;

	BSTNode * d = treePredecessor(isNode(tree, 11));
	deleteNode(tree, d);
	inorder(tree);
	cout << endl;

	

	system("pause");
	return 0;
}