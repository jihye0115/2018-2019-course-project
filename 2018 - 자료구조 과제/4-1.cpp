// linked_stack.cpp : Defines the entry point for the console application.
//

//#include <stdafx.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int element;

typedef struct DlistNode {
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;


void init(DlistNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

int is_empty(DlistNode *phead)
{
	return (phead->llink == NULL);
}

void push(DlistNode *phead, element item)
{
	DlistNode *temp = (DlistNode *)malloc(sizeof(DlistNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	else {
		temp->data = item;
		temp->llink = phead;
		temp->rlink = phead->rlink;
		phead->rlink = temp;
	}
}

element pop(DlistNode *phead)
{
	if (is_empty(phead)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		DlistNode *temp = phead->rlink;
		int item = temp->data;
		phead->rlink = phead->rlink->rlink;
		free(temp);
		return item;
	}
}

element peek(DlistNode *phead)
{
	if (is_empty(phead)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return phead->rlink->data;
	}
}

int main()
{
	DlistNode *phead = (DlistNode *)malloc(sizeof(DlistNode));

	init(phead);
	push(phead, 1);
	push(phead, 2);
	push(phead, 3);

	printf("%d\n", pop(phead));
	printf("%d\n", pop(phead));
	printf("%d\n", pop(phead));
}

