#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

const unsigned int MAX_FACTORS = 64;
static pthread_mutex_t mtxCpt;
static pthread_mutex_t mtxPrint;
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

	pthread_mutex_lock(&mtxPrint);
	printf("%ju: ",n);
	for(j=0; j<k; j++)
	{
	printf("%ju ",factors[j]);
	}
	printf("\n");
	pthread_mutex_unlock(&mtxPrint);
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
	pthread_mutex_init(&mtxPrint,NULL);

	pthread_create(&threadID1,NULL,routine,NULL);
	pthread_create(&threadID2,NULL,routine,NULL);	
	pthread_join(threadID1,NULL);
	pthread_join(threadID2,NULL);
	
	fclose(file);
	pthread_mutex_destroy(&mtxCpt);
	pthread_mutex_destroy(&mtxPrint);
	pthread_exit(NULL);
}
