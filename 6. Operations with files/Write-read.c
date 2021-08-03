#include <stdio.h>
#include <unistd.h>

int main()
{
	FILE *fp;
	char filename[10]= "testfile";
	char testtext[50] = "test 123 test";
	char testgettext[100];
	char testlseektext[100];
	char buffer[2];
	int i = 0;
	int size = 0;

	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("\nCan't open file writing!\n");
		getchar();
		return -1;
	}
	printf("\n Write text to file: %s\n", testtext);
	fputs(testtext, fp);
	fclose(fp);

	fp = NULL;
	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		printf("\nCan't open file for reading!\n");
		getchar();
		return -2;
	}
	fgets(testgettext, 100, fp);
	printf("\n Read text from file: %s\n", testgettext);
	fclose(fp);	

	fp = NULL;
	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		printf("\nCan't open file for reading (lseek)!\n");
		getchar();
		return -3;
	}		
	size = lseek(fileno(fp), 0, SEEK_END);
	if (-1 == size)
	{
		printf("\nlseek fail!\n");
		return -4;
	} 

	for(i = 0; i<=size; i++)
	{
		lseek(fileno(fp), -(i), SEEK_END);
		read(fileno(fp), buffer, 1);
		if(i>0)
		{
			testlseektext[i-1] = buffer[0]; //костыль
		}		
	}
	printf("\n lseek text: %s\n", testlseektext);
	return 0;
}