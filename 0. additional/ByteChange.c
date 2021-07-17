#include <stdio.h>

int main(){
	int a = 0x00DDAABB;
	int c = 0xCC;
	printf("c = %x \n", c);
	printf("a = %x \n", a);

	char *ptra;
	ptra = (char*)&a;
	ptra+=2;
	*ptra = c;
	printf("*ptra = c = %x \n", *ptra);
	printf("result a = %x \n", a); 
	return 0;
}