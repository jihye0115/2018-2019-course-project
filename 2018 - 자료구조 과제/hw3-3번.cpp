#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;
typedef struct ListNode {  //node 구조체 정의
	element data;
	struct ListNode *link;
} ListNode;

typedef struct {  //리스트의 head와 tail을 저장한 구조체
	ListNode *head;// Head pointer
	ListNode *tail;// Tail pointer
	int length;// # of nodes
} ListType;

//Initialization
void init(ListType *plist)
{
	plist->length = 0; //노드의 개수는 0
	plist->head = NULL; //list is blank
	plist->tail = NULL;
}

//whether or not the list is empty
int is_empty(ListType *plist)
{
	if (plist->head == NULL) return 1;  //when the list is blank return 1
	else return 0;
}

// Return node pointer of ‘pos’ in the list.
ListNode *get_node_at(ListType *plist, int pos)
{
	ListNode *tmp_node = plist->head;
	if (pos < 0) return NULL;
	for (int i = 0; i < pos; i++)
		tmp_node = tmp_node->link;  //pos위치의 노드의 주소를 저장
	return tmp_node;
}

void add_first(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

	temp->data = a;  //새로운 노드를 생성하여 데이터 저장
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		temp->link = plist->head;  //원래 리스트의 첫번째 노드를 새 노드에 연결
		plist->head = temp;  //리스트의 head pointer에 새 노드의 주소 저장
	}
	plist->length++; //the number of elements of list argument
}

void add_last(ListType *plist, int a)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

	temp->data = a;  //새로운 노드를 생성하여 데이터 저장
	temp->link = NULL;

	if (plist->head == NULL) { //when list is blank
		plist->head = temp;
		plist->tail = temp;
	}
	else {
		plist->tail->link = temp;  //원래 리스트의 마지막 노드에 새 노드를 연결
		plist->tail = temp;  //리스트의 tail pointer가 새 노드를 가리키도록 주소 저장
	}
	plist->length++; //the number of elements of list argument
}

// Insert new data at the ‘position’
void add(ListType *plist, int position, element data)
{
	ListNode *p;
	if ((position >= 0) && (position <= plist->length)) {
		ListNode *node = (ListNode *)malloc(sizeof(ListNode));
		if (node == NULL) printf_s("Memory allocation error");
		node->data = data;
		node->link = NULL;
		p = get_node_at(plist, position - 1);  //새 노드를 저장할 위치의 앞 노드 주소
		node->link = p->link;  //p의 뒤에 오던 노드를 새 노드에 연결
		p->link = node;  //p와 새 노드 연결
		plist->length++;  //the number of elements of list argument
	}
}

// Display data in the buffer.
void display(ListType *plist)
{
	ListNode *node = plist->head;  //node에 첫 노드의 주소 저장
	printf("( ");
	for (; node; ) {  //node의 link가 null을 가리킬때까지 출력
		printf("%d ", node->data);
		node = node->link;  //다음 노드의 주소 저장
	}
	printf(")\n");
}

// delete a data at the ‘pos’ in the list
void del(ListType *plist, int pos)
{
	if (!is_empty(plist) && (pos >= 0) && (pos < plist->length)) {
		ListNode *p;
		p = get_node_at(plist, pos - 1);  //삭제할 노드의 앞 노드 주소
		ListNode *removed;
		removed = get_node_at(plist, pos);  //삭제할 노드의 주소
		p->link = removed->link;  //p와 삭제할 노드의 뒤 노드를 연결
		plist->length--;
	}
}

void delete_first(ListType *plist)
{
	if (plist->head == NULL) {
		printf("The list is blank.\n");
	}
	else {
		plist->head = plist->head->link;  //head pointer에 두번째 노드를 연결
		plist->length--;  //리스트의 노드 개수 1개 줄임
	}
}

void delete_last(ListType *plist)
{
	if (plist->head == NULL) {
		printf("The list is blank.\n");
	}
	else {
		ListNode *p;
		p = get_node_at(plist, plist->length - 2);  //뒤에서 두번째 노드
		p->link = NULL;  //p가 삭제할 노드 대신 null을 가리킴
		plist->tail = p;  //tail pointer가 p를 가리켜야 함
		plist->length--;  //리스트의 노드 개수 1개 줄임
	}
}
// Find a node whose data = item
int is_in_list(ListType *plist, element item)
{
	ListNode *p;
	p = plist->head;  //p에 첫번째 노드 주소 저장
	while ((p != NULL)) {
		if (p->data == item)  //p에 있는 데이터가 받은 item과 같으면 break
			break;
		p = p->link;  //다음 노드로 이동
	}
	if (p == NULL) return 0;  //일치하는 데이터가 없었으면 0
	else return 1;  //일치하는 데이터가 있었으면 1
}

// Return the data at the ‘pos’.
int get_entry(ListType *plist, int pos)
{
	ListNode *p;
	if (pos >= plist->length) printf("Position error");
	p = get_node_at(plist, pos);  //pos위치의 node 주소를 저장
	return p->data;  //pos 위치의 data return
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
