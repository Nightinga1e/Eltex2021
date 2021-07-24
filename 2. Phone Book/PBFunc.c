#include <stdio.h>
#include <string.h>

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

void trashclean()
{
	while(getchar()!='\n');
}
int Add()
{	
	clrscr();
	trashclean();
	printf("\n Enter name: \n");
	fgets(my_pb[counter].name, 12, stdin);
	
	printf("\n Enter number: \n");
	fgets(my_pb[counter].number, 12, stdin);

	counter++;
	printf("\nPress Enter to continue\n");
	trashclean();	
	clrscr();
	return 0;
}

int Show()
{
	clrscr();
	for(int i=0; i<counter; i++)
	{
		if(my_pb[i].name[0]!=0)
		{
			printf("\n№ = %d", i + 1);
			printf("\nName:\n");
			puts(my_pb[i].name);
			printf("Number:\n");
			puts(my_pb[i].number);	
		}	
	}
	printf("\n Press Enter to continue.\n");
	getchar();
	trashclean();
	clrscr();
	return 0;
}

int Find()
{
	clrscr();
	trashclean();
	
	char findname[12];
	int findfl = 0;
	int abonentnum = -1;
	printf("\n Enter name to find abonent: \n");
	fgets(findname, 12, stdin);
	for(int i=0; i<counter; i++)
	{
		if ((strncmp(findname, my_pb[i].name, sizeof(findname))) == 0)
		{
			findfl = 1;
			printf("\nAbonent number is:\n");
			puts(my_pb[i].number);
			abonentnum = i;
		}
	}
	if(findfl ==0)
	{
		printf("\n Can't find abonent. \n");
	}
	printf("\n Press Enter to continue.\n");
	trashclean();
	clrscr();
	return abonentnum;
}

int Del()
{
	clrscr();
	int abonentnum = Find();
	int item = 0;
	if(abonentnum != -1){
		printf("\n Do you want to delete this abonent?  1 - yes /2 - no \n");
		scanf("%d", &item);
		if(item==1)
		{
			my_pb[abonentnum].name[0] = 0;
			my_pb[abonentnum].number[0] = 0;
		}
	printf("\n Deleted. Press Enter to continue. \n");
	getchar();
	trashclean();
	clrscr();
	}
	return 0;
}