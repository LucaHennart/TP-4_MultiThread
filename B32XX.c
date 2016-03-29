#include <stdint.h>
#include <stdio.h>

//QUESTION 1
int is_prime(uint64_t p)
{	uint64_t premier = 0;
	uint64_t i=2;
	while (i<p && premier==0)
	{	if (p%i==0)
		{	premier=1;
		}
		i++;
	}
	return premier;
}

//QUESTION 2
void print_prime_factors(uint64_t n)
{	printf("%ld:", n);
	uint64_t i=2;
	while (i<=n)
	{	if (n%i==0)
		{	printf(" %ld", i);
			n=n/i;
		} else
		{	i++;
		}	
	}
	printf("\r\n");
}

void read_file(const char * fileName)
{	uint64_t number;
	FILE * file = NULL;
	file=fopen(fileName,"r");
	if (file != NULL)
	{	while (fscanf(file,"%ld",&number) != EOF)
		{	print_prime_factors(number);
		}
	} else
	{	printf("Impossible d'ouvrir le fichier.");
	} 
	fclose(file);
}

int main ()
{	read_file("in.txt");
	return 0;
}
