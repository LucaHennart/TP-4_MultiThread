#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

const unsigned int MAX_FACTORS = 64;
static pthread_mutex_t mtxCpt;
static pthread_mutex_t mtxPrint;
static FILE *file;

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
{	const char *fileName = "generated_numbers_question2.txt";
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
