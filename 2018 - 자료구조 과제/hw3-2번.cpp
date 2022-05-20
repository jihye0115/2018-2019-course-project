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
	plist->length = 0; //노드의개수는0
	plist->head = NULL; //list is blank
	plist->tail = NULL;
}

void add_last(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
	temp->data = a;  //새로운노드를생성하여데이터저장
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		plist->tail->link = temp;  //원래리스트의마지막노드에새노드를연결
		plist->tail = temp;  //리스트의tail pointer가새노드를가리키도록주소저장
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
	ListNode *node = plist->head;  //node에첫노드의주소저장
	printf("( ");
	for (; node; ) {  //node의link가null을가리킬때까지출력
		printf("%d ", node->data);
		node = node->link;  //다음노드의주소저장
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
	add_last(&alist, 15); add_last(&alist, 20); add_last(&alist, 25); //alist에데이터저장
	add_last(&blist, 3); add_last(&blist, 7); add_last(&blist, 8); add_last(&blist, 15);
	add_last(&blist, 18); add_last(&blist, 30);  //blist에데이터저장
	ListType *clist = merge(&alist, &blist);
	display(&alist);
	display(&blist);
	display(clist);
}