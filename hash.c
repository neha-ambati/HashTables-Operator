#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"hash.h"

struct Performance *newPerformance (){
	struct Performance *per;
	/* malloc struct */
	per = malloc(sizeof(struct Performance));

	/* initialize variables in struct  */
	per->reads = 0;
	per->writes = 0;
	per->mallocs = 0;
	per->frees = 0;

	/* if malloc fails, exit out of program */
	if(per == NULL){
		fprintf(stderr, "%s", "ERROR\n");
		exit(0);
	}

return per;
}

struct HashTable *createTable (struct Performance *performance, unsigned int capacity, int (*hash)(void*, int), int (*compar)(const void*, const void*)){
int i;
	
    struct HashTable *hashT;
    /* malloc struct */
    hashT = malloc(sizeof(struct HashTable));

	/* if malloc fails, exit out of program */
	if(hashT == NULL){
		fprintf(stderr, "%s", "ERROR\n");
		exit(0);
	}

	/* malloc data in struct */
	hashT->data = (malloc (capacity * sizeof(void *) ) );

	/* if malloc fails, exit out of program */
	if(hashT->data == NULL){
		fprintf(stderr, "%s", "ERROR\n");
		exit(0);
	}

	/* initialize variables in struct  */
	hashT->capacity = capacity;
	hashT->hash = hash;
	hashT->compar = compar;
	hashT->nel = 0;

	/* set value of each pointer equal to NULL */
	for(i=0; i<(hashT->capacity); i++){
		hashT->data[i] = NULL;
		(performance->reads)++; //reads counter
	}
	(performance->mallocs)++; //mallocs counter

return hashT;
}

void addElement (struct Performance *performance, struct HashTable *table, void *src){
/* declare variables */
int index;

	/* if malloc fails, exit out of program */
	if ((table->nel) == (table->capacity)){
		fprintf(stderr, "%s", "ERROR\n");
		exit(0);
	} 

	index = table->hash(src,table->capacity);// sets index
	
    while ( table->data[index] != NULL ) {
        index = (index + 1)%(table->capacity);
        performance->reads++;
    }

	
	table->data[index] = src; //null is found so copies src into data
	(table->nel)++; //nel counter
	(performance->writes)++; //writes counter
} 


int getIdx (struct Performance *performance, struct HashTable *table, void *src){
/* declare variables */
int orginal = 0;
int index = table->hash(src, table->capacity); // sets and initializes index
int i = index;

    while ( ( i != index ) || (orginal == 0) ) {
        orginal = 1;
        if ( table->data[i] != NULL){
            if ( table->compar ( src , table->data[i] ) == 0 ) {
                performance->reads++; //reads counter
                return i;
            }
            performance->reads++; //reads counter
        }
        i = ( i + 1 )%(table->capacity);
    }
    return -1;
}

void freeTable (struct Performance *performance, struct HashTable *table){
	free(table->data);
    free(table);
    performance->frees++; //frees counter 
}

void *getElement (struct Performance *performance, struct HashTable *table, void *src){
int index = getIdx(performance, table, src);
	if(index == -1){
		return NULL;
	} else {
		return table->data[index];
	}

}

void removeElement (struct Performance *performance, struct HashTable *table, void *target){
int index = getIdx(performance, table, target);
	if(index == -1){
		return;
	} else {
		table->data[index] = NULL;
		(performance->writes)++;
		(table->nel)--;
		return;
	}

}

int hashAccuracy (struct HashTable *table){
/* declare variables */
int index;
int hashAcc = 0;
int result;

	/* loop through data */
    for ( index = 0 ; index < table->capacity ; index++ ) {
        if ( table->data[index] != NULL ) {
            result = table->hash(table->data[index],table->capacity); // sets result
            if ( index < result ) {
               hashAcc += ( index ) - ( result - table->capacity ); //add index to difference between hash function's value and capacity
            } else {
               hashAcc += ( index ) - result;
            }
        }
    }
    return hashAcc;

}

void rehash (struct HashTable *table){
/* variable declarations */
int index;
int result;

	/* loop through data */
	for(index = 0; index < table->capacity; index++){
		if(table->data[index] != NULL){
		result = table->hash(table->data[index],table->capacity); // sets result

			while((result) != index){
				if(table->data[result] == NULL){
					table->data[result] = table->data[index];
					table->data[index] = NULL;
				}

				result++;

				if(result == table->capacity){
					result = 0;
				}
				
			}
		}

	}
}