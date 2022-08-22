#include <stdio.h>

int inputArray(int a[]);
int OutputArray(int a[], int size);

int main() {
	int a[100]={0}, num, i, size=0;
	
	size = inputArray(a); // 배열 a의 주소
	inputArray(a); // 배열 a의 주소를 전달해줌으로서 inputArray() 함수에서 배열의 입력을 받을 수 있게 한다.
	OutputArray(a, size); // 배열 a의 주소와 크기를 전달해줌으로서 배열의 주소를 알려주어 사용할 수 있게 하고, 크기는 거꾸로 출력할 때 사용한다.

	return 0;
}

int inputArray(int a[]) {
	int i, num;

	for(i = 0; i < 100; i++)
	{
			scanf("%d", &num);
		
		if(num == 0){
			break; 
		} // num에 0이 입력될 경우, for문에서 탈출한다.
		else a[i] = num; // 그게 아닐 경우, a[i]에 num을 할당해준다.
		
	}

	return i - 1;
}

int OutputArray(int a[], int size)
{
	int j;
	
	for(j = size; j >= 0; j--)
		printf("%d ", a[j]);
	
	return j;
}
