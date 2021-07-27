#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsPassOk(void);

int main(void)
{
	int PwStatus;

	puts("Enter password:");
	PwStatus = IsPassOk();
	
	if (PwStatus == 0) {
		printf("Bad password!\n");
		exit(1);
	} else {
		printf("Access granted!\n");
	}

	return 0;
}

int IsPassOk(void)
{
	char Pass[12];

	gets(Pass);

	return 0 == strcmp(Pass, "test");
}

//для компиляции: gcc test.c -fno-stack-protector -no-pi -o test -g
//смотрим нужный адрес возврата, используем converter.c для преобразования адреса
// подаем на вход полученный файл test<command