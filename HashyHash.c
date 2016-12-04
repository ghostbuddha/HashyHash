#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HashyHash.h"

int nextPrime(int n) {
	int i, root, keepGoing = 1;

	if (n % 2 == 0)
		++n;

	while (keepGoing) {
    keepGoing = 0;
    root = sqrt(n);

    for (i = 3; i <= root; i++) {
      if (n % i == 0) {
        n += 2;
        keepGoing = 1;

        break;
      }
    }
  }

	return n;
}

int calc_probe(int capacity, int index, int offset, int probing) {
  return (probing == LINEAR ? (index + offset) : (index + (offset*offset))) % capacity;
}

HashTable *makeHashTable(int capacity) {
  int index;

  HashTable *h = malloc(sizeof(HashTable));

  if (capacity <= 0) capacity = DEFAULT_CAPACITY;

  h->array = malloc(sizeof(int)*capacity);

  for (index = 0; index < capacity; index++) {
    h->array[index] = UNUSED;
  }


  h->capacity = capacity;
  h->size = 0;
  h->hashFunction = NULL;
  h->probing = LINEAR;
  h->stats.opCount = 0;
  h->stats.collisions = 0;

  return h;
}

HashTable *destroyHashTable(HashTable *h) {
  if (h == NULL) return NULL;

  free(h->array);
  free(h);

  return NULL;
}

int setProbingMechanism(HashTable *h, ProbingType probing) {
  if (h == NULL) return HASH_ERR;


  if (probing != LINEAR && probing != QUADRATIC) return HASH_ERR;

  h->probing = probing;

  return HASH_OK;
}

int setHashFunction(HashTable *h, unsigned int (*hashFunction)(int)) {
  if (h == NULL) return HASH_ERR;

  h->hashFunction = hashFunction;

  return HASH_OK;
}

int isAtLeastHalfEmpty(HashTable *h) {
  if (h == NULL) return 0;
  if (h->capacity == 0) return 0;
  if (h->size > (h->capacity)/2) return 0;

  return 1;
}

int expandHashTable(HashTable *h) {
  if (h == NULL) return 0;

  int elem, item, old_capacity = h->capacity, keep_op = h->stats.opCount;
  int *old_array = h->array;

  if (h->probing == LINEAR) h->capacity = (h->capacity * 2) + 1;
  if (h->probing == QUADRATIC) h->capacity = nextPrime((h->capacity*2) + 1);

  h->array = malloc(sizeof(int)*h->capacity);

  for (elem = 0; elem < h->capacity; elem++) {
    h->array[elem] = UNUSED;
  }

  for (elem = 0; elem < old_capacity; elem++) {
    item = old_array[elem];

    if (item != UNUSED) insert(h, item);
  }

  free(old_array);

  h->stats.opCount = keep_op;

  return 1;
}

int insert(HashTable *h, int key) {
  if (h == NULL) return HASH_ERR;
  if (h->hashFunction == NULL) return HASH_ERR;

  if (!isAtLeastHalfEmpty(h)) {
    if (!expandHashTable(h)) return HASH_ERR;
  }

  unsigned int index = h->hashFunction(key) % h->capacity;

  if (h->array[index] == UNUSED) {
    h->array[index] = key;
  } else {
    int iterations, probe;

    h->stats.collisions++;

    for (iterations = 1; iterations <= h->capacity; iterations++) {
      probe = calc_probe(h->capacity, index, iterations, h->probing);

      if (h->array[probe] == UNUSED) {
        h->array[probe] = key;
        break;
      }

      h->stats.collisions++;
    }

    if (iterations > h->capacity) return HASH_ERR;
  }

  h->size++;
  h->stats.opCount++;

  return HASH_OK;
}

int search(HashTable *h, int key) {

}

int delete(HashTable *h, int key) {

}

double difficultyRating(void) {
  return 3.5;
}

double hoursSpent(void) {
  return 10.2;
}

