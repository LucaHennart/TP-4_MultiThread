#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

const unsigned int MAX_FACTORS = 64;

int get_prime_factors(uint64_t n, uint64_t* dest)
{	uint64_t i=2;
	uint64_t cpt=0;

	while (i<=n)
	{	if (n%i==0)
		{	dest[cpt]=i;
			cpt++;
			n=n/i;
		} else
		{	i++;
		}	
	}
	return cpt;
}

void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	k=get_prime_factors(n,factors);
	printf("%ju: ",n);
	for(j=0; j<k; j++)
	{
	printf("%ju ",factors[j]);
	}
	printf("\n");
}

int main(void)
{	print_prime_factors(77); // expected result:   77: 7 11
	print_prime_factors(84); // expected result:   84: 2 2 3 7
}
