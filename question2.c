#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

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

void print_prime_factors(uint64_t n)
{	uint64_t *tab = tabPrime(sqrt(n));
	int isPrimeNumber = isPrime(n,tab);
	printf("%ju:", n);
	if (isPrimeNumber == 1)
	{
		printf(" %ju", n);
	} else
	{
		uint64_t i=2;
		while (isPrime(n,tab) == 0 && i<=n)
		{	if (n%i==0)
			{	printf(" %ju", i);
				n=n/i;
			} else
			{	i++;
			}	
		}
		if (n != 1)
		{
			printf(" %ju", n);
		}
	}
	printf("\r\n");
}

int main(void)
{	const char *fileName = "generated_numbers_question2.txt";
	char *str = malloc(sizeof(char)*25);
	FILE *file=fopen(fileName,"r");
	if (file != NULL)
	{	while (fgets(str,25,file) != NULL)
		{	print_prime_factors(atoll(str));
		}
	} else
	{	printf("Impossible d'ouvrir le fichier.");
	} 
	free(str);
	return 0;
}
