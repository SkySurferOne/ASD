#include <iostream>
using namespace std;

struct BSTNode {
	BSTNode * up;
	BSTNode * left;
	BSTNode * right;
	int key;
};

void inorder(BSTNode * v) {
	if (v != NULL) {
		inorder(v->left);
		cout << v->key << " ";
		inorder(v->right);
	}
}

bool addNode(BSTNode * &tree, int key) {
	if (tree == NULL) {
		tree = new BSTNode;
		if (tree == NULL) return false;
		tree->key = key;
		tree->left = NULL;
		tree->right = NULL;
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
		tmp->left = tmp->right = NULL;
		if (key <= cp->key)
			cp->left = tmp;
		else 
			cp->right = tmp;
		return true;
	}
}

BSTNode * isNode(BSTNode * v, int key) {
	while (v != NULL && key != v->key) {
		if (key < v->key) 
				v = v->left;
		 else
				v = v->right;
	}
	return v;
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
	cout << isNode(tree, 1)->key << endl;
	cout << isNode(tree, 8)->key << endl;
	cout << isNode(tree, 11)->key << endl;
	cout << isNode(tree, 55) << endl;
	cout << isNode(tree, -1) << endl;
	system("pause");
	return 0;
}