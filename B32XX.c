#include <stdint.h>
#include <stdio.h>

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

int main ()
{	printf("%d\r\n", 13543);
	printf("%d\r\n", is_prime(13543));
	
	printf("%d\r\n", 24857);
	printf("%d\r\n", is_prime(24857));

	printf("%d\r\n", 95873);
	printf("%d\r\n", is_prime(95873));
	
	return 0;
}
