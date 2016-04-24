#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

void *print_prime_factors(void *nb)
{	uint64_t n = (uint64_t) nb;
	printf("%ju:", n);
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
	pthread_exit(NULL);
}

int main(void)
{	const char *fileName = "generated_numbers_question3_best_efficiency.txt";
	char *str1 = malloc(sizeof(char)*25);
	char *str2 = malloc(sizeof(char)*25);
	pthread_t threadID1;
	pthread_t threadID2;
	FILE *file=fopen(fileName,"r");
	if (file != NULL)
	{	while (fgets(str1,25,file) != NULL && fgets(str2,25,file) != NULL)
		{	pthread_create(&threadID1,NULL,print_prime_factors,(void *)(atoll(str1)));
			pthread_create(&threadID2,NULL,print_prime_factors,(void *)(atoll(str2)));
			pthread_join(threadID1,NULL);
			pthread_join(threadID2,NULL);
		}
	} else
	{	printf("Impossible d'ouvrir le fichier.");
	} 
	free(str1);
	free(str2);
	pthread_exit(NULL);
}
