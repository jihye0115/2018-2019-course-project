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

TreeNode *tree_predecessor(TreeNode *p)
{
	TreeNode *y;
	y = p;
	if (p->left != NULL)
	{
		y = y->left;  //일단 왼쪽 주소로 이동하여 왼쪽 subtree에 접근
		while (y->right != NULL)
		{
			y = y->right; //가장 오른쪽까지 이동
		}
		return y;  //the rightmost node
	}
	y = p->parent; //왼쪽 자식이 없으므로 부모 노드로 이동
	while (y != NULL && p == y->left) {
		p = y;
		y = y->parent; //만약 자신이 누군가의 왼쪽 노드였다면 아닐때까지 부모 노드로 이동
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
	while (q->right) q = q->right;
	do
	{
		printf("%c\n", q->data); // Output data
		// Call the predecessor
		q = tree_predecessor(q);
	} while (q); // If not null
}
