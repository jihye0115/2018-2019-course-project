#include <stdio.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right, *parent;
} TreeNode;
//       G
//    C     F
// A   B   D   E
TreeNode n1 = { 'A', NULL, NULL, NULL };
TreeNode n2 = { 'B', NULL, NULL, NULL };
TreeNode n3 = { 'C', &n1, &n2, NULL };
TreeNode n4 = { 'D', NULL, NULL, NULL };
TreeNode n5 = { 'E', NULL, NULL, NULL };
TreeNode n6 = { 'F', &n4, &n5, NULL };
TreeNode n7 = { 'G', &n3, &n6, NULL };
TreeNode *exp = &n7;

TreeNode *tree_successor(TreeNode *p)
{
	TreeNode *y;
	y = p;
	if (p->right != NULL)
	{
		y = y->right;  //일단 오른쪽 주소로 이동하여 오른쪽 subtree에 접근
		while (y->left != NULL)
		{
			y = y->left; //가장 왼쪽까지 이동
		}
		return y;  //the leftmost node
	}
	y = p->parent; //오른쪽 자식이 없으므로 부모 노드로 이동
	while (y != NULL && p == y->right) {
		p = y;
		y = y->parent; //만약 자신이 누군가의 오른쪽 노드였다면 아닐때까지 부모 노드로 이동
	}
	return y;
}
void main()
{
	TreeNode *q = exp;
	n1.parent = &n3;
	n2.parent = &n3;
	n3.parent = &n7;
	n4.parent = &n6;
	n5.parent = &n6;
	n6.parent = &n7;
	n7.parent = NULL;

	// Go to the leftmost node
	while (q->left) q = q->left;
	do
	{
		printf("%c\n", q->data); // Output data
		// Call the successor
		q = tree_successor(q);
	} while (q); // If not null
}
