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
	while (child-1 <= h->heap_size) {
		if ((child-1 < h->heap_size) && (h->heap[child-1].key) > h->heap[child].key)
			child++;
		if (temp.key <= h->heap[child-1].key) break;
		h->heap[parent-1] = h->heap[child-1];
		parent = child;
		child *= 2;
	}
	h->heap[parent-1] = temp;

	return item;
}

void Decrease_key_min_heap(HeapType *A, int i, int key)
{
	if (key >= A->heap[i].key)
		printf("new key is not smaller than current key");

	A->heap[i].key = key;
	int a = i;
	element tmp = A->heap[i];
	while ((a != 0) && (key < A->heap[(a+1)/2-1].key)) {
		A->heap[a] = A->heap[(a + 1) / 2 - 1];	//�ڽ��� �θ���� ���Ͽ� �ڽ��� ������ ���� �̵�
		a = (a + 1) / 2 - 1;
	}
	A->heap[a] = tmp;		//�ڸ�ã�� ����
}

void print_prim(HeapType *h, int s)
{
	int tmp;
	for (int i = 1; i < MAX_VERTICES; i++)
	{
		for (tmp = 0;;tmp++)
		{
			if (h->heap[tmp].index == i) break;
		}
		printf("Vertex %d -> %d \t\t edge:%d\n", h->heap[tmp].p, i, h->heap[tmp].key);
	}
}

void prim(int s, int n)		//s�� ���� ����� �ε���
{
	int i, u, v, tmp;
	for (u = 0; u < n; u++)
	{
		dist[u] = INF;		//ũ�� �񱳸� ���� ���Ѵ�� �ʱ�ȭ
		selected[u] = FALSE;		//���� �ƹ� ��嵵 ���� �ʾҴ�
	}
	dist[s] = 0;		//���0���� ���0������ �Ÿ��� 0

	element *node = (element *)malloc(sizeof(element)*n);
	for (int k = 0; k < n; k++)		//�� �����͸� ������ ��� ����
	{
		node[k].key = dist[k];		//dist�� �ʱ�ȭ
		node[k].p = NULL;		//�θ� ����� �ε����� ������ ���� p
		node[k].index = k;		//����� �ε����� ���� ����
	}

	HeapType *h = (HeapType *)malloc(sizeof(HeapType));		//min heap for priority queue
	h->heap = (element *)malloc(sizeof(element)*(n + 1));
	init(h);
	for (int k = 0; k < n; k++) insert_min_heap(h, node[k]);	//priority queue�� ��� ����
    
	//output�� min heap���� ������ ������ �����ϱ� ���� heap
	HeapType *output = (HeapType *)malloc(sizeof(HeapType));		
	output->heap = (element *)malloc(sizeof(element)*n);
	init(output);

	
	for (i = 0; i < n; i++)
	{
		element temp = delete_min_heap(h);	//min heap���� ������ ��带 temp�� ����
		insert_min_heap(output, temp);		//output�� temp�����صα�
		u = temp.index;		//temp�� �ε����� u�� �Ҵ��Ͽ� ���� ���� ����
		selected[u] = TRUE;	
		if (dist[u] == INF) return;
		for (v = 0; v < n; v++)
		{
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])		//�����ϸ�, dist[]���� weight�� ���� ��带 ����
				{
					//heap�ȿ��� ������ ���̹Ƿ� index�� ������ ��带 ã�� ���� ����
					for (tmp = 0;; tmp++)
					{
						if (h->heap[tmp].index == v) break;		
					}
					h->heap[tmp].p = temp.index;		//p�� �θ� ����� �ε��� ����
					Decrease_key_min_heap(h, tmp, weight[u][v]);		//����
					dist[v] = weight[u][v];
				}

		}

	}
	print_prim(output, 0);	//����Ʈ
}

int main()
{
	prim(0, MAX_VERTICES);	//���� �ε����� ũ�� ����
}