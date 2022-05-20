#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BUCKETS 10
#define DIGITS 4
#define NUM 1000
int list[NUM];

void counting_sort(int list[], int k) {
	int c[BUCKETS];  //�� ���ڰ� �����ϴ� �󵵼��� ������ �迭
	int b[NUM];		//sorting�� �����͸� ������ �迭
	for (int i = 0; i < BUCKETS; i++) c[i] = 0;		//�󵵸� ��� 0���� �ʱ�ȭ
	for (int j = 0; j < NUM; j++) {
		c[(list[j] % (int)pow(10, k)) / (int)pow(10, k - 1)] += 1;			//�� ���ڰ� �����Ҷ����� �� 1 ����
	}
	for (int n = 1; n < BUCKETS; n++) c[n] += c[n - 1];		//���� �� ����
	for (int m = NUM - 1; m >= 0; m--) {
		b[c[(list[m] % (int)pow(10, k)) / (int)pow(10, k - 1)]-1] = list[m];		//list�� ������ ���ں��� �迭 b�� ���ڸ� ã�� ���� 
		c[(list[m] % (int)pow(10, k)) / (int)pow(10, k - 1)] -= 1;		//�Ҵ��� �������� ��� �� 1 ����
	}
	for(int tmp=0; tmp<NUM; tmp++) list[tmp] = b[tmp];		//�迭 b�� list�� �ٽ� ����
}

void radix_sort(int list[], int n)
{
	for(int i=0; i<DIGITS; i++) counting_sort(list, i+1);	//�ڸ�����ŭ �Լ� ȣ��
}

int main()
{
	srand(time(NULL));
	
	for (int i = 0; i < NUM; i++) {
		list[i] = rand() % 10000;		//���� ���ڸ� ������ list ����
	}

	//Print out the input data
	printf("Input data\n");
	for (int i = 0; i < NUM; i++)
		printf("%5d\t", list[i]);
	printf("\n");

	radix_sort(list, NUM);

	//Print out the sorted data
	printf("Sorted data\n");
	for (int i = 0; i < NUM; i++)
		printf("%5d\t", list[i]);
	printf("\n");

	return 0;
}