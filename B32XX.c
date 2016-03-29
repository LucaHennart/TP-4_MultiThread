#include <stdint.h>
#include <stdio.h>

//QUESTION 1
int is_prime(uint64_t p)
{	uint64_t premier = 0;
	uint64_t i=2;
	while (i<p && premier==0)
	{	if (p%i==0)
		{	premier=1;
		}
		i++;
	}
	return premier;
}

void print_prime_factors(uint64_t n)
{	printf("%d:", n);
	uint64_t i=2;
	while (i<n)
	{	if (n%i==0)
		{	printf("%d ", i);
		}
		i++;
	}
}

int main ()
{	print_prime_factors(15);
	return 0;
}
