#include <stdio.h>

int main()
{
	int const size = 3;
	int array[size][size];
	for (int i=0; i<size; i++){
		for (int j=0; j<size; j++){
			array[i][j] = i*3+j+1;
			printf("%d ", array[i][j]);		
		}
		printf("\n");
	}
	return 0;
}