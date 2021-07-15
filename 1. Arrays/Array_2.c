#include <stdio.h>

int main()
{
	int const size = 5;
	int array[size];
	for (int i=0; i<size; i++)
	{
		array[i] = i+1;
		printf("%d ", array[i]);
	}
	printf("\n");
	for (int i=size-1; i>=0; i--)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}