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

void read_file(const char * fileName)
{	uint64_t number = 1;
	FILE *file=fopen(fileName,"r");
	if (file != NULL)
	{	while (fscanf(file,"%lu",&number) != EOF)
		{	
			print_prime_factors(number);
		}
	} else
	{	
		printf("Impossible d'ouvrir le fichier.");
	} 
	fclose(file);
}

int main () 
{	read_file("in.txt");
	return 0;
}
