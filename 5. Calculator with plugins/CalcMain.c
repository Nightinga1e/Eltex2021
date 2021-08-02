#include <stdio.h>
#include "GetVar.h"
#include "CalcAdd.h"
#include "CalcSub.h"
#include "CalcMult.h"
#include "CalcDiv.h"


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
	int result = 0;
	while(fl!=5)
	{
		switch(menu())
		{
			case 1:
				Getab(&a, &b);
				result = Add(&a, &b);
				//printf("\n FROM MAIN:  a = %d, b = %d \n", a,b);
				printf("\n Result: \n%d + %d = %d \n", a, b, result);
				break;
			case 2:
				Getab(&a, &b);
				result = Sub(&a, &b);
				printf("\n Result: \n%d - %d = %d \n", a, b, result);
				break;
			case 3:
				Getab(&a, &b);
				result = Mult(&a, &b);
				printf("\n Result: \n%d * %d = %d \n", a, b, result);
				break;
			case 4:
				Getab(&a, &b);			
				if(b == 0)
				{
					printf("\n Error! b = 0! \n");
					break;
				}
				result = Div(&a, &b);
				printf("\n Result: \n%d / %d = %d \n", a, b, result);
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