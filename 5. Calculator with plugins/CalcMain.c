#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include "CalcAdd.h"
#include "CalcSub.h"
#include "CalcMult.h"
#include "CalcDiv.h"

#define NUMNAMES 30 //максимальное количество подключаемых плагинов
#define NAMELEN 30

struct Names // для имён функций подключенных плагинов
{
	char *name[NAMELEN];	
};

struct Names newnames[NUMNAMES];

int Getab(int *a, int *b) // считываем два целых числа
{
	printf("\n Enter a: \n");
	scanf("%d", a);
	printf("\n Enter b: \n");
	scanf("%d", b);
	return 0;
}

int menu(struct Names mynames[], int numplugs) //вывод меню, составляется из имен функций подключенных плагинов
{
	printf("\nSelect one of the menu items:\n");
	for(int i = 0; i< numplugs; i++)
	{
		printf("\n%d: %s\n", i+1, *mynames[i].name);
	}
	printf("\n%d: Exit. \n", numplugs+1);
	int result = 0;
	scanf("%d", &result);
	return result;	
}


void trashclean() // чтобы убрать \n из ввода
{
	while(getchar()!='\n');
}

int main()
{
	char inputlib[NAMELEN];
	int fl = 0;
	int a = 0;
	int b = 0;
	int result = 0;
	int numplugs = 0;
	struct Names mynames[NUMNAMES];
	struct Names (*func)() = NULL;
	int (*workfunc)() = NULL;
	void *handle[NUMNAMES];
	printf("\n How much plugins do you want to add? \n");
	scanf("%d", &numplugs);
	trashclean();

	for(int i=0; i<numplugs; i++) //считываем имена функций из введенных плагинов, запоминаем хэндл
	{
		handle[i] = NULL;
		printf("\nEnter full lib name (like: ./libcalcadd.so): \n");
		fgets(inputlib, NAMELEN, stdin);

		size_t len = strlen(inputlib);
		if (len > 0 && inputlib[len-1] == '\n') //чтобы убрать \n из введенной строки
		{					
			inputlib[--len] = '\0';
		}
			
		handle[i] = dlopen(inputlib, RTLD_NOW);
		if(NULL == handle)
		{
			printf("\nHandle is NULL!\n");
			dlerror();
			return -1;
		}
		func = (struct Names(*)())dlsym(handle[i], "funcnames");
		if(NULL == func)
		{
			printf("\nfunc is NULL\n");
			dlerror();
			return -2;
		}
		mynames[i] = func();
		printf("\n%s\n", *mynames[i].name);
	}
	int choice = 0;
	while(fl!=10)
	{
		choice = menu(mynames, numplugs);
		if(choice>0 && choice<=numplugs)
		{
			Getab(&a, &b);
			workfunc = NULL;
			workfunc = (int(*)())dlsym(handle[choice-1], *mynames[choice-1].name); //вызываем функцию
			if(NULL == workfunc)
			{
				printf("\nfunc is NULL\n");
				dlerror();
				return -2;
			}				
			result = workfunc(&a, &b);
			printf("\n Result = %d \n", result);
		}
		else if(choice==numplugs+1)
		{		
			fl=10;
		}
		else
		{		
			printf("\nWrong menu item\n");
			//fl = 10;
		}	
	}

	return 0;
}
