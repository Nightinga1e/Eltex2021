#include <stdio.h>
#include "GetVar.h"

int menu() //вывод меню
{
	printf("\nSelect one of the menu items:\n");
	printf("\n1: Addition.\n");
	printf("\n2: Subtraction.\n");
	printf("\n3: Multiplication. \n");
	printf("\n4: Division. \n");
	printf("\n5: Exit. \n");
	int result = 0;
	scanf("%d", &result);
	return result;	
}

int main()
{
	int fl = 0;
	int a = 0;
	int b = 0;
	while(fl!=5)
	{
		switch(menu())
		{
			case 1:
				Getab(&a, &b);
				printf("\n FROM MAIN:  a = %d, b = %d \n", a,b);

				//Add();
				break;
			case 2:
				Getab(&a, &b);
				//Sub();
				break;
			case 3:
				Getab(&a, &b);
				//Mult();
				break;
			case 4:
				Getab(&a, &b);
				//Div();
				break;
			case 5:
				fl=5;
				break;
			default:
				printf("\nWrong menu item\n");
				fl = 5;
				break;
		}	
	}
	return 0;
}