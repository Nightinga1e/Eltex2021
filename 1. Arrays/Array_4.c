#include <stdio.h>

int const size = 5;

void output(int arr[size][size]) // для вывода массива
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			printf("%d   ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	int array[size][size];
	int number = 1;
	int i,j;
	int edge = size - 1; //грань заполняемой стороны квадрата
	
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			array[i][j] = 0;
		}
	}
	
	printf("\n\nFrom edge to center\n\n");
	for (i = 0; i < edge; i++) // от края к центру
	{
		for(j = i; j < edge; j++)
		{
			array[i][j] = number;
			number++;
		}
		
		for(j = i; j < edge; j++)
		{
			array[j][edge] = number;
			number++;
		}

		for(j = edge; j >= i; j--)
		{
			array[edge][j] = number;
			number++;
		}
		
		for(j = edge - 1; j > i; j--)
		{
			array[j][i] = number;
			number++;
		}

		edge--;		
	}

	if(size % 2 == 1)
	{
		array[size / 2][size / 2] = number;
	}

	output(array);

	
	for (i = 0; i < size; i++) // обнуление
	{
		for(j = 0; j < size; j++)
		{
			array[i][j] = 0;
		}
	}
	
	int horizontal = -1;
	int vertical = 1;
	number = size * size;
	int tempi = size / 2;
	int tempj = (size / 2) - 1;
	if(size % 2 == 1)
	{
		horizontal = 1;
		vertical = -1;
		tempj = size / 2;
	}
		
	printf("\n\nFrom center to edge\n\n");
	for (i = 0; i <= size; i++) //от центра к краю
	{
		for(j = 0; j < i; j++)
		{
			array[tempi][tempj] = number;
			tempj+=horizontal;
			number--;
		}	
		if(i!=size) //совсем не костыль
		{
			for(j = 0; j < i; j++)
			{
				array[tempi][tempj] = number;
				tempi+=vertical;		
				number--;
			}
		}
	horizontal = horizontal * (-1);
	vertical = vertical * (-1);
	}
	output(array);
	return 0;
}