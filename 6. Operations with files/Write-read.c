#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	FILE *fp;
	int fd;
	char filename[10]= "testfile";
	char testtext[50] = "test 123 test";
	char testgettext[100] = "";
	char testlseektext[100]= "";
	char buffer;
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

	fd = 0;
	fd = open(filename, O_RDONLY);
	if (0 == fd)
	{
		printf("\nCan't open file for reading (lseek)!\n");
		getchar();
		return -3;
	}		
	size = lseek(fd, 0, SEEK_END);
	if (-1 == size)
	{
		printf("\nlseek fail!\n");
		return -4;
	} 

	for(i = 1; i<=size; i++)
	{
		lseek(fd, -i, SEEK_END);
		read(fd, &buffer, 1);
		testlseektext[i-1] = buffer; 	
	}
	printf("\n lseek text: %s\n", testlseektext);
	close(fd);	
	return 0;
}
