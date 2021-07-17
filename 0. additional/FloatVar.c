#include <stdio.h>

float sum(float test){
	float temp = 0.0;
	for (int i=0; ;i++)
	{
		temp = test;
		test += 1.0;
		if (temp == test)
		{
			printf("%f \n", test);
			break;
		}
	}
	return test;
}


int main()
{
	float test = 0.0;
	printf(" First test \n");		
	test = sum(test);
	printf(" Second test \n");
	test = test + 2;
	test = sum(test);
	printf(" Third test \n");
	test = test + 2;
	test = sum(test);
	return 0;
}