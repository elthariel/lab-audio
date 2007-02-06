#include <stdio.h>
#include <math.h>
#include "mymath.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	int j;
//	printf("%f\n%f\n", power(2, 4), facto(4));
//	printf("%f\n", pi);
	for (i = 0; i < 50; i++)
  		printf("Nb d'iterations : %d, %.35f \n", i, sin(pi / 3.0) - sine(pi / 3.0, i));
// 	printf("test\n");
  system("PAUSE");	
  return 0;
}
