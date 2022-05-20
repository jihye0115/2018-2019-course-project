#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int * heap;
	int heap_size;
}HeapType;

//decrease the element i’s value to ‘key’
void Decrease_key_min_heap(HeapType *A, int i, int key)
{
	if (key >= A->heap[i])
		printf("new key is not smaller than current key");

	A->heap[i] = key;
	int a = i;
	
	while ((a != 1) && (A->heap[a] < A->heap[a / 2])) {	
		A->heap[a] = A->heap[a / 2];	//자신의 부모노드와 비교하여 자신이 작으면 위로 이동
		a /= 2;
	}
	A->heap[a] = key;		//자리찾아 대입
}

//Increase the element i’s value to ‘key’
void Increase_key_min_heap(HeapType *A, int i, int key)
{
	if (key <= A->heap[i])
		printf("new key is not smaller than current key");

	A->heap[i] = key;
	int a = i;

	while ((a != A->heap_size) && (A->heap[a] > A->heap[2 * a])) {
		A->heap[a] = A->heap[2 * a];	//자신의 자식노드와 비교하여 자신이 크면 밑으로 이동
		a *= 2;
	}
	A->heap[a] = key;		//자리찾아 대입
}

void main()
{
	int tmp[] = { 0,1,4,2,7,5,3,3,7,8,9 }; //인덱스를 1부터 시작하기위해 인덱스 0에 0값을 대입
	
	HeapType *h= (HeapType *)malloc(sizeof(HeapType));
	h->heap_size = 10;
	h->heap = tmp;

	printf("Initial data : \n");
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]);  //인덱스 1부터 출력해보기

	Decrease_key_min_heap(h, 4, 3);		//인덱스 4 자리에 3을 넣기
	printf("\n Updated data : \n"); 
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]); 	//확인을 위한 출력

	Increase_key_min_heap(h, 3, 10);	//인덱스 3 자리에 10을 넣기
	printf("\n Updated data : \n");
	for (int i = 1; i < 11; i++)	printf("%d\n", h->heap[i]);		//확인을 위한 출력
}