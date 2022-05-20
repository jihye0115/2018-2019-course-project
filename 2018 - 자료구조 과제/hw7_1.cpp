// selection_sort.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct data {
	int *id;
	int *score;
} data;

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
void selection_sort(data *list, int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list->score[j] < list->score[least]) least = j;
		SWAP(list->score[i], list->score[least], temp);
		SWAP(list->id[i], list->id[least], temp);
	}
}

void selection_sort_stable(data *list, int n)
{
	data *output = (data *)malloc(sizeof(data)); //정렬한 데이터를 저장할 메모리 할당
	output->id = (int *)malloc(sizeof(int)*n);
	output->score = (int *)malloc(sizeof(int)*n);
	if (output == NULL) {
		fprintf(stderr, "can't allocate memory\n");
		exit(1);
	}
	int least, tmp, index = 0;
	for (tmp = n; tmp > 0; tmp--) {
		least = 0;
		for (int j = 1; j < tmp; j++)
			if (list->score[j] < list->score[least]) least = j;		//minimum data가 저장되어 있는 index를 찾아 least에 저장
		output->score[index] = list->score[least];		//minimum data를 output에 복사
		output->id[index++] = list->id[least];
		for (int k = least; k < tmp - 1; k++) {
			list->score[k] = list->score[k + 1];		//minimum data를 삭제하기 위해 한칸씩 앞으로 이동.
			list->id[k] = list->id[k + 1];
		}
	}
	for (int t = 0; t < n; t++) {
		list->id[t] = output->id[t];		//output을 다시 list에 저장
		list->score[t] = output->score[t];
	}
	free(output);
}

int main()
{
	int data_id[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int data_score[] = { 30, 25, 10, 20, 80, 30, 25, 10 };

	int in_size = 8;
	data *input = (data *)malloc(sizeof(data));

	input->id = data_id;
	input->score = data_score;

	//Print out the input data
	printf("Input data\n");
	for (int i = 0; i < in_size; i++)
		printf("%d\t %d\n", input->id[i], input->score[i]);
	printf("\n");

	// Produce the stable sorting results by replacing 'selection_sort' with 'selection_sort_stable'.
	selection_sort_stable(input, in_size);

	//Print out the sorted data
	printf("Sorted data\n");
	for (int i = 0; i < in_size; i++)
		printf("%d\t %d\n", input->id[i], input->score[i]);
	printf("\n");

	return 0;
}