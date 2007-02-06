
#include "mymath.h"



double		power(double a, unsigned int b) // Compute a^b;
{
	double res;
	
	res = 1;
	while (b)
	{
		res *= a;
		b--;
	}
	return res;
}

double		facto(unsigned int i) //Compute i!
{
	double	res;
	
	res = 1;
	while (i)
	{
		res *= i;
		i--;
	}
	return res;
}

double		sine(double d, int iter)
{
	double	res;
	int		flag;
	int		i;
	double	tmp;
	
	flag = 0;
	res = 0;
	i = 0;
	while (i <= iter)
	{
		tmp = power(-1, i);
		tmp *= power(d, 2 * i + 1) / facto(2 * i + 1);
		res += tmp;
		i++;
	}
	
	return(res);
}
