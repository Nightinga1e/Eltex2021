#include <stdio.h>

struct PB
	{
		char name[12];
		char number[12];
	};

struct PB my_pb[100];

int counter = 0;

void clrscr()
{
	printf("\e[1;1H\e[2J");
}
int Add()
{	
	clrscr();
	char trash[20]; // some sort of crutch
	fgets(trash,20, stdin);	
		
	printf("\n Enter name: \n");
	fgets(my_pb[counter].name, 12, stdin);
	
	printf("\n Enter number: \n");
	fgets(my_pb[counter].number, 12, stdin);

	counter++;
	printf("\nPress any key to continue\n");	
	getchar();
	clrscr();
	return 0;
}

int Show()
{
	clrscr();
	for(int i=0; i<counter; i++)
	{
		printf("\n№ = %d",i+1);
		printf("\nName:\n");
		puts(my_pb[i].name);
		printf("Number:\n");
		puts(my_pb[i].number);	
	}
	printf("\n Press any key to continue.\n");
	getchar();
	getchar();
	clrscr();
	return 0;
}

int Find()
{

	return 0;
}

int Del()
{

	return 0;
}