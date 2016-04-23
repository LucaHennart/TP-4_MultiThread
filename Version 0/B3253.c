#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    


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
{	printf("%lu:", n);
	uint64_t i=2;
	while (i<=n)
	{	if (n%i==0)
		{	printf(" %lu", i);
			n=n/i;
		} else
		{	i++;
		}	
	}
	printf("\r\n");
}

void read_file(const char * fileName)
{	
	uint64_t number = 1;
	FILE *file=fopen(fileName,"r");
	if (file != NULL)
	{	
		while (fscanf(file,"%lu",&number) != EOF)
		{	
			print_prime_factors(number);
		}
	} else
	{	
		printf("Impossible d'ouvrir le fichier.");
	} 
	fclose(file);
}

void *lancerLeTravail(void* tmp)
	{          
    	uint64_t nombre =  *( ( uint64_t* ) tmp );  
		print_prime_factors(nombre);
		pthread_exit(0);
	}


void lancerLeTravailQuestion6()
{
	pthread_t  thread1;

	FILE *file=fopen("in.txt","r");

	uint64_t nombre1;
	

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	


	/*int pthread_mutex_lock(pthread_mutex_t *mut);
	int pthread_mutex_unlock(pthread_mutex_t *mut);*/
	for(;;)
	{	
		pthread_mutex_lock(&mutex);
		if(fscanf(file,"%lu",&nombre1) == EOF)
		{
			break;
		}
		pthread_create ( &thread1 , NULL,  &lancerLeTravail, &nombre1);
		pthread_mutex_unlock (&mutex);
		//pthread_join(thread1, NULL);
	}
	fclose(file);
	pthread_mutex_destroy( &mutex );
	exit(0);
}

// Pour mesurer le temps d'execution, faire time ./B3228
int main () 
{	

	/*******************Execution Question 1*******************/	
	
	/*
	uint64_t nombre=1;
	printf("Rentre ton nombre : ");
	scanf("%lu",&nombre);
	
	int resPremier = is_prime(nombre);
	
	if(resPremier == 0)
	{
		printf("Nombre : %lu ; Résultat : %s\n",nombre, " Premier");
	}
	else
	{
		printf("Nombre : %lu ; Résultat : %s\n",nombre, " Non Premier");
	}
	*/

	/*******************Fin Execution Question 1*******************
	



	/*******************Execution Question 2 + 3*******************/
	
	/*read_file("in.txt");*/
	
	/*******************Fin Execution Question 2 + 3*******************/



	/*******************Execution Question 4 *******************/
	/*pthread_t  thread1;
	pthread_t  thread2;

	FILE *file=fopen("in.txt","r");

	uint64_t nombre1;
	uint64_t nombre2;

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_destroy( &mutex );


	/*int pthread_mutex_lock(pthread_mutex_t *mut);
	int pthread_mutex_unlock(pthread_mutex_t *mut);*/
	
	/*for(;;)
	{	
		if(fscanf(file,"%lu",&nombre1) == EOF)
		{
			s;
		}
		if(fscanf(file,"%lu",&nombre2) == EOF)
		{
			break;
		}
		pthread_create ( &thread1 , NULL,  &lancerLeTravail, &nombre1);
		//printf("\n");
		pthread_create ( &thread2 , NULL,  &lancerLeTravail, &nombre2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}
	fclose(file);
	exit(0);*/
	
	/*******************Fin Execution Question 4 *******************/






	/*******************Execution Question 6 *******************/
	
	//lancerLeTravailQuestion6();
	//lancerLeTravailQuestion6();
	/*******************Fin Execution Question 6 *******************/
	return 0;
}
