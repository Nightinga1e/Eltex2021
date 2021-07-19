#include <stdio.h>

int main(){
	int a = 0x00DDAABB;
	int c = 0xCC;
	printf("a = %x \n", a);
	printf("c = %x \n", c);

	char *ptra;
	ptra = (char*)&a;
	ptra+=2;
	*ptra = c;
	printf("*ptra = c = %x \n", *ptra);
	printf("result a = %x \n", a); 
	
	a = 0x00DDAABB;
	c = 0x00110000;
	printf("\na = %x \n", a);
	printf("c = %x \n", c);

	a = a-c;
	printf("result a = %x \n", a);
	return 0;
}