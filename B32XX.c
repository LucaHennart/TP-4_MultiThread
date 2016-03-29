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
{	printf("%d:", n);
	uint64_t i=2;
	while (i<=n)
	{	if (n%i==0)
		{	printf(" %d", i);
			n=n/i;
		} else
		{	i++;
		}	
	}
	printf("\r\n");
}

int main ()
{	print_prime_factors(12488);
	return 0;
}
