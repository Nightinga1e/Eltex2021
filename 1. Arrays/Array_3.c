#include <stdio.h>

int main()
{
	int const size = 5;
	int array[size][size];

	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			if(i+j < size-1){
				array[i][j]=0;
			}else{
				array[i][j]=1;
			}			
			printf("%d", array[i][j]);
		}
		printf("\n");
	}
	return 0;
}