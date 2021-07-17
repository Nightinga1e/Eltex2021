#include <stdio.h>

float sumfloat(float test){
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

double sumdouble(double test){
	double temp = 0.0;
	for (int i=0; ;i++)
	{
		temp = test;
		test += 1.0;
		/*if (temp == test)
		{
			printf("%f \n", test);
			break;
		}*/
		if (i>16777224)
		{
			printf("%f \n", test);
		}
	}
	return test;
}

int main()
{
	float test = 0.0;
	printf(" First float test \n");		
	test = sumfloat(test);
	printf(" Second test \n");
	test = test + 2.0;
	test = sumfloat(test);
	printf(" Third test \n");
	test = test + 2.0;
	test = sumfloat(test);
	
	double test2 = 0.0;
	printf(" First double test \n");
	test2 = sumdouble(test2);
	
	return 0;
}