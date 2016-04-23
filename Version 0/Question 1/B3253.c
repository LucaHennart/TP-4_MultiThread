#include <stdint.h>
#include <stdio.h>

void print_prime_factors(uint64_t n)
{	printf("%ju:", n);
	uint64_t i=2;
	while (i<=n)
	{	if (n%i==0)
		{	printf(" %ju", i);
			n=n/i;
		} else
		{	i++;
		}	
	}
	printf("\r\n");
}

int main () 
{	print_prime_factors(84);
	print_prime_factors(101);
	return 0;
}
