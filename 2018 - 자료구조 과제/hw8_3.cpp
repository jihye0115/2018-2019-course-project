#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_VERTICES 8
#define INF 1000L
#define TRUE 1
#define FALSE 0

int weight[MAX_VERTICES][MAX_VERTICES] =
{ { 0,3,INF,INF,INF,INF,INF,14 },
{ 3,0,8,INF,INF,INF,INF,10 },
{ INF,8,0,15,2,INF,INF,INF },
{ INF,INF,15,0,INF,INF,INF,INF },
{ INF,INF,2,INF,0,9,4,5 },
{ INF,INF,INF,INF,9,0,INF,INF },
{ INF,INF,INF,INF,4,INF,0,6 },
{ 14,10,INF,INF,5,INF,6,0 } };

// Elements used in the heap
typedef struct element {
	int index;
	int key;   // frequency of each character
	int p;
	element *pnode;
} element;
//Min Heap for priority queue
typedef struct HeapType {
	element *heap;
	int heap_size;
} HeapType;
int dist[MAX_VERTICES];
int selected[MAX_VERTICES];

void init(HeapType *h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = (h->heap_size)++;

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 0) && (item.key < h->heap[(i + 1) / 2 - 1].key)) {
		h->heap[i] = h->heap[(i + 1) / 2 - 1];
		i = (i + 1) / 2 - 1;
	}
	h->heap[i] = item; // Insert new node
}

element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[0];
	temp = h->heap[--(h->heap_size)];
	parent = 1;
	child = 2;
	while (child - 1 <= h->heap_size) {
		if ((child - 1 < h->heap_size) && (h->heap[child - 1].key) > h->heap[child].key)
			child++;
		if (temp.key <= h->heap[child - 1].key) break;
		h->heap[parent - 1] = h->heap[child - 1];
		parent = child;
		child *= 2;
	}
	h->heap[parent - 1] = temp;

	return item;
}

void Decrease_key_min_heap(HeapType *A, int i, int key)
{
	if (key >= A->heap[i].key)
		printf("new key is not smaller than current key");

	A->heap[i].key = key;
	int a = i;
	element tmp = A->heap[i];
	while ((a != 0) && (key < A->heap[(a + 1) / 2 - 1].key)) {
		A->heap[a] = A->heap[(a + 1) / 2 - 1];	//자신의 부모노드와 비교하여 자신이 작으면 위로 이동
		a = (a + 1) / 2 - 1;
	}
	A->heap[a] = tmp;		//자리찾아 대입
}

void print_dijkstra(HeapType *h, int s, int n)
{
	for (int m=0; m < n; m++)
	{
		for (int k=0; k < n; k++) //부모인덱스를 가지고 부모 노드의 주소를 pnode에 저장
		{
			if (h->heap[m].p == h->heap[k].index)
				h->heap[m].pnode = &(h->heap[k]);
		}
	}
	int a, num=0, temp;
	printf("Enter arrival vertex : ");
	scanf_s("%d", &a);		//마지막 노드 입력받음
	for (temp = 0;; temp++)
	{
		if (h->heap[temp].index == a) break;
	}
	element * tmp = &(h->heap[temp]);
	int *output = (int *)malloc(sizeof(int)*n);
	output[0] = a;		//output에 마지막 노드 인덱스부터 점차 저장
	int sum = tmp->key;	//총 거리는 마지막 노드의 key에 저장되어있음
	for (int in=1; in < n; in++)
	{
		output[in] = tmp->p;
		tmp = tmp->pnode;		//부모 노드로 옮겨가며 output에 부모 노드의 인덱스 저장
		num++;
		if (tmp->index == 0) break;
	}
	printf("Shortest path : ");
	for (int i = num; i > 0; i--)
	{
		printf(" v%d ->", output[i]);		//output에 저장된 인덱스를 다시 거꾸로 출력
	}
	printf(" v%d ", output[0]);			//마지막 노드 출력
	printf("\nShortest path distance : %d", sum);
}

void dijkstra(int s, int n)		//s는 시작 노드의 인덱스
{
	int i, u, v, tmp;
	for (u = 0; u < n; u++)
	{
		dist[u] = INF;		//크기 비교를 위해 무한대로 초기화
		selected[u] = FALSE;		//아직 아무 노드도 고르지 않았다
	}
	dist[s] = 0;		//노드0에서 노드0까지의 거리는 0

	element *node = (element *)malloc(sizeof(element)*n);
	for (int k = 0; k < n; k++)		//각 데이터를 저장할 노드 생성
	{
		node[k].key = dist[k];		//dist로 초기화
		node[k].p = NULL;		//부모 노드의 인덱스를 저장할 변수 p
		node[k].index = k;		//노드의 인덱스를 따로 저장
		node[k].pnode = NULL;
	}

	HeapType *h = (HeapType *)malloc(sizeof(HeapType));		//min heap for priority queue
	h->heap = (element *)malloc(sizeof(element)*(n + 1));
	init(h);
	for (int k = 0; k < n; k++) insert_min_heap(h, node[k]);	//priority queue에 노드 정렬

	//output은 min heap에서 삭제한 노드들을 저장하기 위한 heap
	HeapType *output = (HeapType *)malloc(sizeof(HeapType));
	output->heap = (element *)malloc(sizeof(element)*n);
	init(output);


	for (i = 0; i < n; i++)
	{
		element temp = delete_min_heap(h);	//min heap에서 삭제한 노드를 temp에 저장
		insert_min_heap(output, temp);		//output에 temp저장해두기
		u = temp.index;		//temp의 인덱스를 u에 할당하여 시작 노드로 지정
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		for (v = 0; v < n; v++)
		{
			if (weight[u][v] != INF)
				if (!selected[v] && dist[u] + weight[u][v] < dist[v])		//인접하며, dist[]보다 weight가 작은 노드를 선택
				{
					//heap안에서 섞였을 것이므로 index가 동일한 노드를 찾기 위한 과정
					for (tmp = 0;; tmp++)
					{
						if (h->heap[tmp].index == v) break;
					}
					h->heap[tmp].p = temp.index;		//p에 부모 노드의 인덱스 저장
					dist[v] = dist[u] + weight[u][v];
					Decrease_key_min_heap(h, tmp, dist[v]);		//갱신
				}

		}

	}
	print_dijkstra(output, 0, MAX_VERTICES);
}

int main()
{
	dijkstra(0, MAX_VERTICES);	//시작 인덱스와 크기 전송
}