#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BUCKETS 10
#define DIGITS 4
#define NUM 1000
int list[NUM];

void counting_sort(int list[], int k) {
	int c[BUCKETS];  //각 숫자가 등장하는 빈도수를 저장할 배열
	int b[NUM];		//sorting된 데이터를 저장할 배열
	for (int i = 0; i < BUCKETS; i++) c[i] = 0;		//빈도를 모두 0으로 초기화
	for (int j = 0; j < NUM; j++) {
		c[(list[j] % (int)pow(10, k)) / (int)pow(10, k - 1)] += 1;			//각 숫자가 등장할때마다 빈도 1 증가
	}
	for (int n = 1; n < BUCKETS; n++) c[n] += c[n - 1];		//누적 빈도 생성
	for (int m = NUM - 1; m >= 0; m--) {
		b[c[(list[m] % (int)pow(10, k)) / (int)pow(10, k - 1)]-1] = list[m];		//list의 마지막 숫자부터 배열 b에 제자리 찾아 저장 
		c[(list[m] % (int)pow(10, k)) / (int)pow(10, k - 1)] -= 1;		//할당한 데이터의 경우 빈도 1 감소
	}
	for(int tmp=0; tmp<NUM; tmp++) list[tmp] = b[tmp];		//배열 b를 list에 다시 복사
}

void radix_sort(int list[], int n)
{
	for(int i=0; i<DIGITS; i++) counting_sort(list, i+1);	//자리수만큼 함수 호출
}

int main()
{
	srand(time(NULL));
	
	for (int i = 0; i < NUM; i++) {
		list[i] = rand() % 10000;		//랜덤 숫자를 가지는 list 생성
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