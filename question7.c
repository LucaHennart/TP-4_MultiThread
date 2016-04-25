#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

const unsigned int MAX_FACTORS = 64;

uint64_t * tabPrime (uint64_t max)
{
	uint64_t *dP = (uint64_t*) malloc ((max/3)*sizeof(uint64_t));
	dP[1] = 2;
	dP[2] = 3;
	dP[3] = 5;
	unsigned int sommet = 4;
	uint64_t i;
	unsigned int pasI = 4;
	unsigned int essai;
	unsigned int j;
	for (i = 7 ; i < max ; i += pasI, pasI = 6 - pasI)
	{	
		for (essai = dP[j = 1] ; (i % essai) && (essai * essai < i) ; essai = dP[++j]);
		if (i % essai)
		{
			dP[sommet++] = i;
		}
	}
	dP[0]=sommet;
	return dP;
}

int isPrime (uint64_t n, uint64_t *tabPrime)
{	int i;
	for (i = 1 ; i < tabPrime[0] ; i++)
	{
		if (n % tabPrime[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}


int get_prime_factors(uint64_t n, uint64_t* dest)
{	uint64_t cpt=0;

	uint64_t *tab = tabPrime(sqrt(n));
	int isPrimeNumber = isPrime(n,tab);

	if (isPrimeNumber == 1)
	{
		dest[0]=n;
		return 1;
	} else
	{
		uint64_t i=2;
		while (isPrime(n,tab) == 0 && i<=n)
		{	if (n%i==0)
			{	dest[cpt]=i;
				cpt++;
				n=n/i;
			} else
			{	i++;
			}	
		}
		if (n != 1)
		{
			dest[cpt]=n;
			cpt++;
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
