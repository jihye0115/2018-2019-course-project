#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int * heap;
	int heap_size;
}HeapType;

//decrease the element i��s value to ��key��
void Decrease_key_min_heap(HeapType *A, int i, int key)
{
	if (key >= A->heap[i])
		printf("new key is not smaller than current key");

	A->heap[i] = key;
	int a = i;
	
	while ((a != 1) && (A->heap[a] < A->heap[a / 2])) {	
		A->heap[a] = A->heap[a / 2];	//�ڽ��� �θ���� ���Ͽ� �ڽ��� ������ ���� �̵�
		a /= 2;
	}
	A->heap[a] = key;		//�ڸ�ã�� ����
}

//Increase the element i��s value to ��key��
void Increase_key_min_heap(HeapType *A, int i, int key)
{
	if (key <= A->heap[i])
		printf("new key is not smaller than current key");

	A->heap[i] = key;
	int a = i;

	while ((a != A->heap_size) && (A->heap[a] > A->heap[2 * a])) {
		A->heap[a] = A->heap[2 * a];	//�ڽ��� �ڽĳ��� ���Ͽ� �ڽ��� ũ�� ������ �̵�
		a *= 2;
	}
	A->heap[a] = key;		//�ڸ�ã�� ����
}

void main()
{
	int tmp[] = { 0,1,4,2,7,5,3,3,7,8,9 }; //�ε����� 1���� �����ϱ����� �ε��� 0�� 0���� ����
	
	HeapType *h= (HeapType *)malloc(sizeof(HeapType));
	h->heap_size = 10;
	h->heap = tmp;

	printf("Initial data : \n");
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]);  //�ε��� 1���� ����غ���

	Decrease_key_min_heap(h, 4, 3);		//�ε��� 4 �ڸ��� 3�� �ֱ�
	printf("\n Updated data : \n"); 
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]); 	//Ȯ���� ���� ���

	Increase_key_min_heap(h, 3, 10);	//�ε��� 3 �ڸ��� 10�� �ֱ�
	printf("\n Updated data : \n");
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]);		//Ȯ���� ���� ���
}