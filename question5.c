#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

static pthread_mutex_t mtxCpt;

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

void *routine(void *fName)
{	const char *fileName = (const char *) fName;	
	char *str = malloc(sizeof(char)*25);
	char *end = malloc(sizeof(char)*25);
	do
	{	pthread_mutex_lock(&mtxCpt);
		FILE *file = fopen(fileName,"r");
		if (file != NULL)
		{	end=fgets(str,25,file);
			fclose(file);
		} else
		{	printf("Impossible d'ouvrir le fichier.");
		} 
		pthread_mutex_unlock(&mtxCpt);
		if (end != NULL)
		{	print_prime_factors(atoll(str));
		}
	} while (end != NULL);
	
	pthread_exit(NULL);
}

int main(void)
{	const char *fileName = "generated_numbers_question2";

	pthread_t threadID1;
	pthread_t threadID2;
	pthread_mutex_init(&mtxCpt,NULL);

	pthread_create(&threadID1,NULL,routine,(void *)fileName);
	pthread_create(&threadID2,NULL,routine,(void *)fileName);	
	pthread_join(threadID1,NULL);
	pthread_join(threadID2,NULL);

	pthread_mutex_destroy(&mtxCpt);
	pthread_exit(NULL);
}
