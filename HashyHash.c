#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <limits.h>

#define UNUSED   INT_MIN
#define DIRTY    INT_MAX
#define HASH_ERR 0
#define HASH_OK  1
#define DEFAULT_CAPACITY 5

HashTable *makeHashTable(int capacity) {

}

HashTable *destroyHashTable(HashTable *h) {

}

int setProbingMechanism(HashTable *h, ProbingType probing) {

}

int setHashFunction(HashTable *h, unsigned int (*hashFunction)(int)) {

}

int isAtLeastHalfEmpty(HashTable *h) {

}

int expandHashTable(HashTable *h) {

}

int insert(HashTable *h, int key) {

}

int search(HashTable *h, int key) {

}

int delete(HashTable *h, int key) {

}

double difficultyRating(void) {

}

double hoursSpent(void) {
    
}


#endif
