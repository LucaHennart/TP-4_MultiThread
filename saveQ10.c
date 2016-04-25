#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>


typedef struct {
uint64_t value;
unsigned int tabSize;
uint64_t* primeNumbers;
} Decomposition;



typedef struct {
    int allocated; /* current allocation of array */
    int filled;    /* number of items present in the binary heap */
    Decomposition **array;    /* array of decomposition pointers */
} BinarySort;

BinarySort * Init(int size);
BinarySort * AdjustSize (BinarySort * tree);
void InsertValue( BinarySort * tree , Decomposition *decomp );
void Destroy(BinarySort * tree);
void test ();

BinarySort * Init(int size)
{  
	BinarySort * tree = (BinarySort *) malloc(sizeof(BinarySort));
	tree -> array = ( Decomposition ** ) malloc( sizeof( Decomposition* ) * size );
    
	tree -> allocated = size;
	tree -> filled = 0;
	int i;
	for ( i = 0 ; i < tree -> allocated ; i++ )
	{	
		tree -> array[i] = NULL;
	}
	return tree;
}

BinarySort * AdjustSize (BinarySort * tree)
{	
	BinarySort * treeAdjusted = Init(tree->allocated*2);
	treeAdjusted->filled=tree->filled;
 	int i;
	for ( i = 0 ; i<tree->allocated ; i++ )
	{	if (tree -> array[i] != NULL)
		{	
			treeAdjusted -> array[i] = tree -> array[i];
		}
	}
	//Destroy( tree );
	return(treeAdjusted);
}

/* InsertValue insert value into the binary heap
 * the array is reallocated if necessary (allocated changed 
 * with respect to the new size )
 * filled is incremented by 1 */
void InsertValue( BinarySort * tree , Decomposition *decomp )
{	int indice = 0;
 	while ( tree -> array[indice] != NULL )
	{	if ( decomp -> value <= tree->array[indice]->value )
		{	
			indice = indice * 2 + 1;
		} else
		{	
			indice = indice * 2 + 2;
		}
	 	while( tree -> allocated <= indice )
		{	
			tree=AdjustSize( tree );
  		}
	}
	tree -> array[indice] = decomp;
	tree -> filled++;
}

/* Destroy frees the structure and the array */
void Destroy( BinarySort * tree )
{   
	free( tree -> array );
    free( tree );
}

void test ()
{	
	BinarySort * tree = Init(10);
	
	uint64_t* nombresPremiers1 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers1[0] = 2;
	nombresPremiers1[1] = 3;
	nombresPremiers1[2] = 5;
	Decomposition *dec1 = (Decomposition*) malloc (sizeof(Decomposition));
	dec1 -> value = 30;
	dec1 -> tabSize = 3;
	dec1 -> primeNumbers = nombresPremiers1;
	
	uint64_t* nombresPremiers2 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers2[0] = 2;
	nombresPremiers2[1] = 2;
	nombresPremiers2[2] = 7;
	Decomposition *dec2 = (Decomposition*) malloc (sizeof(Decomposition));
	dec2 -> value = 28;
	dec2 -> tabSize = 3;
	dec2 -> primeNumbers = nombresPremiers2;
	
	uint64_t* nombresPremiers5 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers5[0] = 29;
	Decomposition *dec5 = (Decomposition*) malloc (sizeof(Decomposition));
	dec5 -> value = 29;
	dec5 -> tabSize = 1;
	dec5 -> primeNumbers = nombresPremiers5;
	
	uint64_t* nombresPremiers3 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers3[0] = 3;
	nombresPremiers3[1] = 3;
	nombresPremiers3[2] = 11;
	Decomposition *dec3 = (Decomposition*) malloc (sizeof(Decomposition));
	dec3 -> value = 99;
	dec3 -> tabSize = 3;
	dec3 -> primeNumbers = nombresPremiers3;
	
	uint64_t* nombresPremiers4 = ( uint64_t* ) malloc( sizeof( uint64_t ) * 64 );
	nombresPremiers4[0] = 2;
	nombresPremiers4[1] = 2;
	Decomposition *dec4 = (Decomposition*) malloc (sizeof(Decomposition));
	dec4 -> value = 4;
	dec4 -> tabSize = 2;
	dec4 -> primeNumbers = nombresPremiers4;
	
	InsertValue(tree,dec1);
	InsertValue(tree,dec4);
	InsertValue(tree,dec2);
	InsertValue(tree,dec5);
	InsertValue(tree,dec3);

	printf("%d\r\n", tree->filled);

	int indiceTab=0;
	int compteurValeur=0;
	int j;
	while ( compteurValeur < tree->filled )
	{	if (tree->array[indiceTab] != NULL)
		{	printf( "indice : " );
			printf( "%d\r\n" , indiceTab );
			printf( "%ju\r\n" , tree->array[indiceTab]->value);
			for ( j = 0 ; j < tree -> array[indiceTab] -> tabSize ; j++ )
			{	
				printf( "%ju\r\n" , tree -> array[indiceTab] -> primeNumbers[j] );
			}
		 	compteurValeur++;
		}
	 	indiceTab++;
	}


	Destroy (tree);


	
}

int main ()
{	
	test( );
	return 0;
}
	

