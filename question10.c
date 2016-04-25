#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

typedef struct Decomposition Decomposition;

typedef struct Decomposition {
	uint64_t value;
	unsigned int sizePrimeNumbers;
	uint64_t *primeNumbers;
	Decomposition *left;
	Decomposition *right;
} Decomposition;


const unsigned int MAX_FACTORS = 64;
static pthread_mutex_t mtxCpt;
static pthread_mutex_t mtxPrint;
static pthread_mutex_t mtxStruct;
static FILE *file;
static Decomposition *decomposition;



void AddDecomposition (Decomposition **tree, uint64_t value, unsigned int sizePrimeNumbers, uint64_t *primeNumbers)
{	Decomposition *top;                               			// Décomposition au-dessus de l'insertion
	Decomposition *test = *tree;

	Decomposition *elem = (Decomposition*) malloc (sizeof(Decomposition));	// Décomposition à insérer
	elem->value=value;
 	elem->sizePrimeNumbers=sizePrimeNumbers;
	elem->primeNumbers=primeNumbers;
	elem->left=NULL;
	elem->right=NULL;

	if (test != NULL)											// Si l'arbre n'est pas vide
	{	do														// Faire
		{		
			top = test;											// Prendre la valeur de la tête (top)
			if (value > test -> value)							// Si la valeur que l'on veut rentrer est supérieure à la valeur de la tête
			{	
				test = test -> right;							// On se déplace vers la droite
				if (test == NULL)	
				{	
					top -> right = elem;						// On place la décomposition nouvellement créée si on est en bas de l'arbre
					//printf("%s:\r\n","On a Add");
				}
			} 
			else												//  Si la valeur que l'on veut rentrer est inférieure ou égale à la valeur de la tête
			{	
				test = test -> left;							// On se déplace vers la gauche
				if (test == NULL)
				{	
					top -> left = elem;							// On place la décomposition nouvellment créée si on est en bas de l'arbre
					//printf("%s:\r\n","On a Add");
				}
			}
		} while (test != NULL);									// On fait cela tant que l'on arrive pas en bas
	} else 
	{	
		*tree = elem;											// Sinon on le place directement
		//printf("%s:\r\n","On a Add");
	}
}

/*void Print(Decomposition *tree)
{
	if (tree == NULL)
	{	
		return;
	}
	if (tree->left != NULL)
	{
		Print(tree->left);
	}
	printf("Cle = %ju\r\n", tree->value);
	if (tree->right != NULL)
	{
		Print(tree->right);
	}
}*/

Decomposition * FindValue (Decomposition *tree, uint64_t value)
{	
	Decomposition *tmp = tree;
 	while (tmp != NULL && tmp -> value != value)
	{	
		if (value <= tmp->value)
		{	
			tmp = tmp -> left;
		} 
	 	else 
		{	
			tmp = tmp -> right;
		}
	}
	if (tmp == NULL)
	{	
		return NULL;
	} 
 	else
	{
		return tmp;
	}
	
}

void Destroy (Decomposition ** tree)
{	Decomposition *tmpTree = *tree;
	if (tree == NULL)
	{	
		return;
	}
	if (tmpTree -> left != NULL)
	{	
		Destroy(&tmpTree -> left);
	}
	if (tmpTree -> right != NULL)
	{	
		Destroy(&tmpTree -> right);
	}
	free(tmpTree);
	*tree = NULL;
}

/*void test ()
{	Decomposition *decomposition = NULL;

	uint64_t* nombresPremiers1 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers1[0] = 2;
	nombresPremiers1[1] = 3;
	nombresPremiers1[2] = 5;
	
	uint64_t* nombresPremiers2 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers2[0] = 2;
	nombresPremiers2[1] = 2;
	nombresPremiers2[2] = 7;
	
	uint64_t* nombresPremiers3 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers3[0] = 3;
	nombresPremiers3[1] = 3;
	nombresPremiers3[2] = 11;
	
	uint64_t* nombresPremiers4 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers4[0] = 2;
	nombresPremiers4[1] = 2;

	uint64_t* nombresPremiers5 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers5[0] = 29;

	AddDecomposition(&decomposition,30,3,nombresPremiers1);
	AddDecomposition(&decomposition,28,3,nombresPremiers2);
	AddDecomposition(&decomposition,99,3,nombresPremiers3);
	AddDecomposition(&decomposition,4,2,nombresPremiers4);
	AddDecomposition(&decomposition,29,1,nombresPremiers5);
 
 	Print(decomposition);
 
 	Decomposition *find = FindValue(decomposition,99);
 	if (find != NULL)
	{	printf("%ju\r\n",find->value);
	} else
	{	printf("%s\r\n","PAS TROUVE");
	}

	Destroy(&decomposition);
}*/

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

unsigned int get_prime_factors(uint64_t n, uint64_t* dest)
{	uint64_t *tab = tabPrime(sqrt(n));
	int isPrimeNumber = isPrime(n,tab);

	uint64_t i=2;
	unsigned int cpt=0;
 	Decomposition *dec;

	while (i<=n)
	{	
		pthread_mutex_lock(&mtxStruct);
		dec = FindValue(decomposition,n);
		pthread_mutex_unlock(&mtxStruct);
		if (dec != NULL)
		{	
			int j;
			for (j = 0 ; j < dec -> sizePrimeNumbers ; j++)
			{	
				dest[j+cpt]=dec->primeNumbers[j];
			 	cpt++;
			}
		} else if (n%i==0)
		{	
			dest[cpt]=i;
			cpt++;
			n=n/i;
		} else
		{	
			i++;
		}	
	}
 	pthread_mutex_lock(&mtxStruct);
 	AddDecomposition(&decomposition,n,cpt,dest);
 	//printf("%s:\r\n","On a Add");
  	pthread_mutex_unlock(&mtxStruct);
	return cpt;
}

void print_prime_factors(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	unsigned int j,k;
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
	{	
		pthread_mutex_lock(&mtxCpt);
		if (file != NULL)
		{	
			end=fgets(str,25,file);
		} else
		{	
			printf("Impossible d'ouvrir le fichier.");
		} 
		pthread_mutex_unlock(&mtxCpt);

		if (end != NULL)
		{	
			print_prime_factors(atoll(str));
		}
	} while (end != NULL);

	free(str);
	free(end);
	
	pthread_exit(NULL);
}

int main(void)
{	const char *fileName = "generated_different_numbers_question10.txt";
	file = fopen(fileName,"r");
 	decomposition = NULL;

	pthread_t threadID1;
	pthread_t threadID2;
	pthread_mutex_init(&mtxCpt,NULL);
	pthread_mutex_init(&mtxPrint,NULL);
 	pthread_mutex_init(&mtxStruct,NULL);

	pthread_create(&threadID1,NULL,routine,NULL);
	pthread_create(&threadID2,NULL,routine,NULL);	
	pthread_join(threadID1,NULL);
	pthread_join(threadID2,NULL);
	
	fclose(file);
 	Destroy(&decomposition);
	pthread_mutex_destroy(&mtxCpt);
	pthread_mutex_destroy(&mtxPrint);
 	pthread_mutex_destroy(&mtxStruct);
	pthread_exit(NULL);
}
