#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;
typedef struct ListNode {  //node ����ü ����
	element data;
	struct ListNode *link;
} ListNode;

typedef struct {  //����Ʈ�� head�� tail�� ������ ����ü
	ListNode *head;// Head pointer
	ListNode *tail;// Tail pointer
	int length;// # of nodes
} ListType;

//Initialization
void init(ListType *plist)
{
	plist->length = 0; //����� ������ 0
	plist->head = NULL; //list is blank
	plist->tail = NULL;
}

//whether or not the list is empty
int is_empty(ListType *plist)
{
	if (plist->head == NULL) return 1;  //when the list is blank return 1
	else return 0;
}

// Return node pointer of ��pos�� in the list.
ListNode *get_node_at(ListType *plist, int pos)
{
	ListNode *tmp_node = plist->head;
	if (pos < 0) return NULL;
	for (int i = 0; i < pos; i++)
		tmp_node = tmp_node->link;  //pos��ġ�� ����� �ּҸ� ����
	return tmp_node;
}

void add_first(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

	temp->data = a;  //���ο� ��带 �����Ͽ� ������ ����
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		temp->link = plist->head;  //���� ����Ʈ�� ù��° ��带 �� ��忡 ����
		plist->head = temp;  //����Ʈ�� head pointer�� �� ����� �ּ� ����
	}
	plist->length++; //the number of elements of list argument
}

void add_last(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

	temp->data = a;  //���ο� ��带 �����Ͽ� ������ ����
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		plist->tail->link = temp;  //���� ����Ʈ�� ������ ��忡 �� ��带 ����
		plist->tail = temp;  //����Ʈ�� tail pointer�� �� ��带 ����Ű���� �ּ� ����
	}
	plist->length++; //the number of elements of list argument
}

// Insert new data at the ��position��
void add(ListType *plist, int position, element data)
{
	ListNode *p;
	if ((position >= 0) && (position <= plist->length)) {
		ListNode *node = (ListNode *)malloc(sizeof(ListNode));
		if (node == NULL) printf_s("Memory allocation error");
		node->data = data;
		node->link = NULL;
		p = get_node_at(plist, position - 1);  //�� ��带 ������ ��ġ�� �� ��� �ּ�
		node->link = p->link;  //p�� �ڿ� ���� ��带 �� ��忡 ����
		p->link = node;  //p�� �� ��� ����
		plist->length++;  //the number of elements of list argument
	}
}

// Display data in the buffer.
void display(ListType *plist)
{
	ListNode *node = plist->head;  //node�� ù ����� �ּ� ����
	printf("( ");
	for (; node; ) {  //node�� link�� null�� ����ų������ ���
		printf("%d ", node->data);
		node = node->link;  //���� ����� �ּ� ����
	}
	printf(")\n");
}

// delete a data at the ��pos�� in the list
void del(ListType *plist, int pos)
{
	if (!is_empty(plist) && (pos >= 0) && (pos < plist->length)) {
		ListNode *p;
		p = get_node_at(plist, pos - 1);  //������ ����� �� ��� �ּ�
		ListNode *removed;
		removed = get_node_at(plist, pos);  //������ ����� �ּ�
		p->link = removed->link;  //p�� ������ ����� �� ��带 ����
		plist->length--;
	}
}

void delete_first(ListType *plist)
{
	if (plist->head == NULL) {
		printf("The list is blank.\n");
	}
	else {
		plist->head = plist->head->link;  //head pointer�� �ι�° ��带 ����
		plist->length--;  //����Ʈ�� ��� ���� 1�� ����
	}
}

void delete_last(ListType *plist)
{
	if (plist->head == NULL) {
		printf("The list is blank.\n");
	}
	else {
		ListNode *p;
		p = get_node_at(plist, plist->length - 2);  //�ڿ��� �ι�° ���
		p->link = NULL;  //p�� ������ ��� ��� null�� ����Ŵ
		plist->tail = p;  //tail pointer�� p�� �����Ѿ� ��
		plist->length--;  //����Ʈ�� ��� ���� 1�� ����
	}
}
// Find a node whose data = item
int is_in_list(ListType *plist, element item)
{
	ListNode *p;
	p = plist->head;  //p�� ù��° ��� �ּ� ����
	while ((p != NULL)) {
		if (p->data == item)  //p�� �ִ� �����Ͱ� ���� item�� ������ break
			break;
		p = p->link;  //���� ���� �̵�
	}
	if (p == NULL) return 0;  //��ġ�ϴ� �����Ͱ� �������� 0
	else return 1;  //��ġ�ϴ� �����Ͱ� �־����� 1
}

// Return the data at the ��pos��.
int get_entry(ListType *plist, int pos)
{
	ListNode *p;
	if (pos >= plist->length) printf("Position error");
	p = get_node_at(plist, pos);  //pos��ġ�� node �ּҸ� ����
	return p->data;  //pos ��ġ�� data return
}

int main()
{
	ListType list1;
	init(&list1);
	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);
	del(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);
	printf("%s\n", is_in_list(&list1, 20) == 1 ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));
}
