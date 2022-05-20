// huffman.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 1000
#define MAX_BIT   10
#define MAX_CHAR   20

// Input data for huffman code
typedef struct input_huff {
	char *data;      // Character array (a ~ f)
	int *freq;      // Frequency array
	int size;      // Number of characters
} input_huff;

// Structure for huffman binary tree
typedef struct TreeNode {
	char data;         // Character (a ~ f)
	int key;         // Frequency
	int bits[MAX_BIT];   // Huffman codeword
	int bit_size;      // Huffman codeword's size
	struct TreeNode *l;   // Left child of huffman binary tree
	struct TreeNode *r;   // Right child of huffman binary tree
} TreeNode;

// Structure for bits stream
typedef struct bits_stream {
	int *stream;
	int length;
} bits_stream;

// Elements used in the heap
typedef struct element {
	TreeNode *ptree;
	int key;   // frequency of each character
} element;

// Heap
typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

int **m_LUT, *m_bit_size;
int   m_char_size = 6;

// Initialization
void init(HeapType *h)
{
	h->heap_size = 0;
}
//
int is_empty(HeapType *h)
{
	if (h->heap_size == 0)
		return true;
	else
		return false;
}

void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// Node generation in binary tree
TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	node->l = left;
	node->r = right;
	return node;
}

// Binary tree removal
void destroy_tree(TreeNode *root)
{
	if (root == NULL) return;
	destroy_tree(root->l);
	destroy_tree(root->r);
	free(root);
}

// Huffman code generation
element huffman_tree(input_huff *huff)
{
	int i;
	TreeNode *node, *x;
	HeapType heap;
	element e, e1, e2;
	init(&heap);

	int n = huff->size;

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ptree = node;
		node->data = huff->data[i];
		e.key = node->key = huff->freq[i];
		memset(node->bits, 0, sizeof(int)*MAX_BIT);
		node->bit_size = 0;

		insert_min_heap(&heap, e);
	}

	for (i = 1; i < n; i++) {
		// Delete two nodes with minimum values
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);

		// Merge two nodes
		x = make_tree(e1.ptree, e2.ptree);
		e.ptree = x;
		x->data = NULL;
		e.key = x->key = e1.key + e2.key;
		memset(x->bits, 0, sizeof(int)*MAX_BIT);
		x->bit_size = 0;

		insert_min_heap(&heap, e);
	}
	e = delete_min_heap(&heap); // Final Huffman binary tree

	return e;
	//   destroy_tree(e.ptree);
}


void huffman_traversal(TreeNode *node)
{
	if (node->l != NULL) {
		int i1,x;
		for (i1 = 0; i1<node->bit_size; i1++)
			node->l->bits[i1] = node->bits[i1];  //부모 노드의 bits를 자식 노드에 복사
		node->l->bits[i1++] = 0;  //복사받은 bits 뒤에 0을 추가해줌
		node->l->bit_size = i1;  //사이즈가 결정됨
		huffman_traversal(node->l);  //재귀함수로 서브 트리에 똑같이 적용
		huffman_traversal(node->r);
	}
	if (node->r != NULL) {
		int i2;
		for (i2 = 0; i2 < node->bit_size; i2++)
			node->r->bits[i2] = node->bits[i2];  //부모 노드의 bits를 자식 노드에 복사
		node->r->bits[i2++] = 1;   //복사받은 bits 뒤에 1을 추가해줌
		node->r->bit_size = i2;  //사이즈가 결정됨
		huffman_traversal(node->l);  //재귀함수로 서브 트리에 똑같이 적용
		huffman_traversal(node->r);
	}
	if (node->l == NULL && node->r == NULL) {  //마지막 노드일 때, 자신의 호프만 코드를 룩업테이블에 저장
		switch (node->data) {			//각 문자에 대해 룩업테이블에 1열씩 저장
		case 'a':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[0][j] = node->bits[j];	//비트 복사
			m_bit_size[0] = node->bit_size;		//비트 사이즈 저장
			break;
		case 'b':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[1][j] = node->bits[j];
			m_bit_size[1] = node->bit_size;
			break;
		case 'c':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[2][j] = node->bits[j];
			m_bit_size[2] = node->bit_size;
			break;
		case 'd':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[3][j] = node->bits[j];
			m_bit_size[3] = node->bit_size;
			break;
		case 'e':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[4][j] = node->bits[j];
			m_bit_size[4] = node->bit_size;
			break;
		case 'f':
			for (int j = 0; j < node->bit_size; j++)
				m_LUT[5][j] = node->bits[j];
			m_bit_size[5] = node->bit_size;
			break;
		}
	}
}
// Generate the huffman codeword from the huffman binary tree
// Hint: use the recursion for tree traversal
// input: root node
// output: m_LUT, m_bit_size
int **mem_2D_int(int row, int col)
{
	int **m2 = (int **)malloc(sizeof(int *)*row);
	for (int i = 0; i < row; i++)
		m2[i] = (int *)malloc(sizeof(int)*col);
	return m2;
}

void print_codeword()
{
	printf("* Huffman codeword\n");
	for (int i = 0; i < m_char_size; i++)
	{
		switch (i) {
		case 0:
			printf("%c: ", 'a');
			break;
		case 1:
			printf("%c: ", 'b');
			break;
		case 2:
			printf("%c: ", 'c');
			break;
		case 3:
			printf("%c: ", 'd');
			break;
		case 4:
			printf("%c: ", 'e');
			break;
		case 5:
			printf("%c: ", 'f');
			break;
		}

		for (int j = 0; j < m_bit_size[i]; j++)
			printf("%d", m_LUT[i][j]);

		printf("\n");
	}

}

// Input: 'str'
// Output: 'bits_stream' (consisting of 0 or 1)
// 'bits_stream' is generated using 'm_LUT' generated by the huffman binary tree
// Return the total length of bits_stream

void huffman_encoding(char *str, bits_stream *bits_str)
{
	int t = 0;
	for (int in = 0; str[in]; in++)
	{
		switch (str[in])		//각 문자에 대해 룩업테이블에서 호프만 코드를 복사해옴
		{
		case 'a': for (int k = 0; ((m_LUT[0][k] == 0) || (m_LUT[0][k] ==1)); k++) bits_str->stream[t++] = m_LUT[0][k]; break;
		case 'b': for (int k = 0; ((m_LUT[1][k] == 0) || (m_LUT[1][k] == 1)); k++) bits_str->stream[t++] = m_LUT[1][k]; break;
		case 'c': for (int k = 0; ((m_LUT[2][k] == 0) || (m_LUT[2][k] == 1)); k++) bits_str->stream[t++] = m_LUT[2][k]; break;
		case 'd': for (int k = 0; ((m_LUT[3][k] == 0) || (m_LUT[3][k] == 1)); k++) bits_str->stream[t++] = m_LUT[3][k]; break;
		case 'e': for (int k = 0; ((m_LUT[4][k] == 0) || (m_LUT[4][k] == 1)); k++) bits_str->stream[t++] = m_LUT[4][k]; break;
		case 'f': for (int k = 0; ((m_LUT[5][k] == 0) || (m_LUT[5][k] == 1)); k++) bits_str->stream[t++] = m_LUT[5][k]; break;
		}
	}
	int interval = t;
	printf("\n* Huffman encoding\n");
	printf("total length of bits stream: %d\n", interval);
	printf("bits stream: ");
	for (int i = 0; i < interval; i++)
		printf("%d", bits_str->stream[i]);
	printf("\n");
}

// input: 'bits_stream' and 'total_length'
// output: 'decoded_str'
int huffman_decoding(bits_stream *bits_str, TreeNode *node, char *decoded_str)
{
	
	int temp[100];
	for(int tmp=0; (bits_str->stream[tmp]==0)|| (bits_str->stream[tmp] == 1);tmp++) temp[tmp] = bits_str->stream[tmp]; //문자열을 temp에 복사

	int k = 0;
	TreeNode * mov = node;
	for (int in = 0 ;  ; )
	{
		if (temp[in] == 0)		//0이면 왼쪽 노드로 이동
		{
			mov = mov->l;
		}
		else if (temp[in] == 1)		//1이면 오른쪽 노드로 이동
		{
			mov = mov->r;
		}
		else break;
		if ((mov->l == NULL) && (mov->r == NULL)) {		//만약 자신에게 자식 노드가 없다면 문자가 결정됨
			decoded_str[k++] = mov->data;		//해당 노드의 문자를 decoded_str에 추가
			mov = node;		//다시 처음부터 탐색하기 위해 mov를 초기화
		}
		in++; 
	}
	int index_char = k;
	printf("\n* Huffman decoding\n");
	printf("total number of decoded chars: %d\n", index_char);
	printf("decoded chars: ");
	for (int i = 0; i < index_char; i++)
		printf("%c", decoded_str[i]);
	printf("\n");

	return index_char;
}

void main()
{
	char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 45, 13, 12, 16, 9, 5 };

	input_huff *huff1 = (input_huff *)malloc(sizeof(input_huff));
	huff1->data = data;
	huff1->freq = freq;
	huff1->size = m_char_size;

	// m_LUT: each row corresponds to the codeword for each character
	// m_bit_size: 1D array of codeword size for each character
	// For instance, a = 0, b = 101, ...
	// 1st row of 'm_LUT': 0 0 ... 0
	// 2nd row of 'm_LUT': 1 0 1 ...0
	// m_bit_size = {1, 3, ...}
	m_LUT = mem_2D_int(m_char_size, MAX_BIT);
	m_bit_size = (int *)malloc(sizeof(int)*m_char_size);

	// Generate the huffman binary tree on heap
	// 'element_root': element containing the root node
	element element_root = huffman_tree(huff1);

	// Generate the huffman codeword from the huffman binary tree
	huffman_traversal(element_root.ptree);
	//insert_m_LUT(element_root.ptree);

	//printf out the huffman codeword
	print_codeword();

	//example of input data
	char str[MAX_CHAR] = { "abacdebaf" };
	//char str[MAX_CHAR] = { "ab" };
	char decoded_str[MAX_CHAR];

	printf("\n* input chars: ");
	for (int i = 0; i < strlen(str); i++)
		printf("%c", str[i]);
	printf("\n");

	//start encoding
	bits_stream *bits_str1 = (bits_stream *)malloc(sizeof(bits_stream));
	bits_str1->stream = (int *)malloc(sizeof(int)*MAX_BIT * MAX_CHAR);
	memset(bits_str1->stream, -1, sizeof(int)*MAX_BIT * MAX_CHAR);
	bits_str1->length = 0;

	huffman_encoding(str, bits_str1);

	//start decoding   
	int decoded_char_length = huffman_decoding(bits_str1, element_root.ptree, decoded_str);
}