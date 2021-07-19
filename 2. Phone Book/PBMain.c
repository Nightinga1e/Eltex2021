#include <stdio.h>
#include "PBFunc.h"

int menu()
{
	printf("\nSelect one of the menu items:\n");
	printf("\n1: Add abonent.\n");
	printf("\n2: Show list of abonents.\n");
	printf("\n3: Find abonent by name. \n");
	printf("\n4: Delete abonent. \n");
	printf("\n5: Exit. \n");
	int result = 0;
	scanf("%d", &result);
	return result;	
}

int main()
{
	int fl = 0;
	while(fl!=5)
	{
		switch(menu())
		{
			case 1:
				Add();
				break;
			case 2:
				Show();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				fl=5;
				break;
			default:
				printf("\nWrong menu item.\n");
				fl = 5;
				break;
		}	
	}
	return 0;
}