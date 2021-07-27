#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char name[20] = "command";
	int input [8];
	char output[28];
	
	for(int i=0; i<28;i++)
	{
		output[i]='1';
	}
	printf("\nВведите адрес для преобразования\n");
	for(int i=0; i<8; i++)
	{
		scanf("%x", &input[i]);
		output[20+i]=(char)input[i];
	}
	
	fp = fopen(name, "w");
	if (fp == NULL)
	{
		printf("\nНе удалось открыть файл\n");
		getchar();
		return -1;
	}
	
	//941140000000000
	fputs(output, fp);
	fclose(fp);
	return 0;
}	