#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

typedef struct {
	ListNode *head; // Head pointer
	ListNode *tail;
	int length; // # of nodes
} ListType;


//Initialization
void init(ListType *plist)
{
	plist->length = 0; //����ǰ�����0
	plist->head = NULL; //list is blank
	plist->tail = NULL;
}

void add_last(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
	temp->data = a;  //���ο��带�����Ͽ�����������
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		plist->tail->link = temp;  //��������Ʈ�Ǹ�������忡����带����
		plist->tail = temp;  //����Ʈ��tail pointer������带����Ű�����ּ�����
	}
	plist->length++; //the number of elements of list argument
}

ListType * merge(ListType *list1, ListType *list2)
{
	ListNode *a = list1->head;
	ListNode *b = list2->head;
	ListType *clist = (ListType *)malloc(sizeof(ListType));
	init(clist);

	while (a && b) {
		if (a->data == b->data) { // a data == b data
			add_last(clist, a->data);
			add_last(clist, b->data);
			a = a->link; b = b->link;
		}
		else if (a->data > b->data) { // a data > b data
			add_last(clist, b->data);
			b = b->link;
		}
		else { // a data < b data
			add_last(clist, a->data);
			a = a->link;
		}
	}
	if (a != NULL) add_last(clist, a->data);
	if (b != NULL) add_last(clist, b->data);
	return clist;
}

// Display data in the buffer.
void display(ListType *plist)
{
	ListNode *node = plist->head;  //node��ù������ּ�����
	printf("( ");
	for (; node; ) {  //node��link��null������ų���������
		printf("%d ", node->data);
		node = node->link;  //����������ּ�����
	}
	printf(")\n");
}

int main()
{
	ListType alist;
	ListType blist;
	init(&alist);
	init(&blist);
	add_last(&alist, 1); add_last(&alist, 2); add_last(&alist, 5); add_last(&alist, 10);
	add_last(&alist, 15); add_last(&alist, 20); add_last(&alist, 25); //alist������������
	add_last(&blist, 3); add_last(&blist, 7); add_last(&blist, 8); add_last(&blist, 15);
	add_last(&blist, 18); add_last(&blist, 30);  //blist������������
	ListType *clist = merge(&alist, &blist);
	display(&alist);
	display(&blist);
	display(clist);
}