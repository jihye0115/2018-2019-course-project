#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right, *parent;
} TreeNode;

void insert_node(TreeNode **root, int key)
{
	TreeNode *p, *t;// p: parent node, t: current node
	t = *root;
	p = NULL;
	// Search first
	while (t != NULL) {
		if (key == t->key) {
			printf("The same key exists in the tree.\n");
			return;
		}
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	// Since the key is not in the tree, insertion is possible.
	TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));  // n: new node to be inserted
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;
	if (p != NULL) {
		if (key < p->key)
			p->left = n;
		else p->right = n;
	}
	else *root = n;
}

void display_node(TreeNode *root)
{	//inorder traversal
	if (root == NULL) return;
	if (root->left) display_node(root->left);
	printf("%d\n", root->key);
	if (root->right) display_node(root->right);
}

void main() {
	srand(time(NULL));

	int input_size = 1000;
	int data_maxval = 10000;
	
	int *input = (int *)malloc(sizeof(int)*input_size);
	
	// Generate an input data randomly
	for (int i = 0; i < input_size; i++)
	{	//size of random number is data_maxval
		input[i] = rand() % data_maxval;
	}

	TreeNode *bst = NULL;
	for (int i = 0; i < input_size; i++)
		insert_node(&bst, input[i]);

	display_node(bst);
}