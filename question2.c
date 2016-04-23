#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
	return 0;
}
