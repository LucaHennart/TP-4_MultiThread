#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

static pthread_mutex_t mtxCpt;
static FILE *file;

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

void *routine()
{	char *str = malloc(sizeof(char)*25);
	char *end = malloc(sizeof(char)*25);
	do
	{	pthread_mutex_lock(&mtxCpt);
		if (file != NULL)
		{	end=fgets(str,25,file);
		} else
		{	printf("Impossible d'ouvrir le fichier.");
		} 
		pthread_mutex_unlock(&mtxCpt);

		if (end != NULL)
		{	print_prime_factors(atoll(str));
		}
	} while (end != NULL);
	
	free(str);
	free(end);
	
	pthread_exit(NULL);
}

int main(void)
{	const char *fileName = "generated_numbers_question6_best_efficiency.txt";
	file = fopen(fileName,"r");

	pthread_t threadID1;
	pthread_t threadID2;
	pthread_mutex_init(&mtxCpt,NULL);

	pthread_create(&threadID1,NULL,routine,NULL);
	pthread_create(&threadID2,NULL,routine,NULL);	
	pthread_join(threadID1,NULL);
	pthread_join(threadID2,NULL);
	
	fclose(file);
	pthread_mutex_destroy(&mtxCpt);
	pthread_exit(NULL);
}
