#include <iostream>
using namespace std;

struct BSTNode {
	BSTNode * up;
	BSTNode * left;
	BSTNode * right;
	int key;
};

// wyœwietla drzewo (niemalej¹co wg wartoœci key)
void inorder(BSTNode * v) {
	if (v != NULL) {
		inorder(v->left);
		cout << v->key << " ";
		inorder(v->right);
	}
}

// dodaje wêze³ do drzewa
bool addNode(BSTNode * &tree, int key) {
	if (tree == NULL) {
		tree = new BSTNode;
		if (tree == NULL) return false;
		tree->key = key;
		tree->left = NULL;
		tree->right = NULL;
		tree->up = NULL;
		return true;
	} else {
		bool run = true;
		BSTNode * cp = tree;
		while (run) {
			if (key <= cp->key) {
				if (cp->left == NULL) 
					run = false;
				else
					cp = cp->left;
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
		if (key <= cp->key)
			cp->left = tmp;
		else 
			cp->right = tmp;
		return true;
	}
}

// zwraca wêze³ o kluczu key (o ile istnieje)
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

// zwraca nastêpnika
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
	cout << endl;
	cout << treePredecessor(isNode(tree, 11))->key << endl;



	system("pause");
	return 0;
}