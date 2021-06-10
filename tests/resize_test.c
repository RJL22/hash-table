#include "../src/hash_table.h"

//Compile command: gcc resize_test.c ../src/hash_table.c ../src/prime_generator.c

int main() {

	char* hashData = malloc(80);
	for (int i = 0; i < 80; i += 2) {
		hashData[i] = (char)(65 + (i / 2));
		hashData[i + 1] = '\0';
	}


	ht_hash_table* hashTable = new_hashtable();

	printf("Initial size: %d\n", hashTable->size);

	for (int i = 0; i < 80; i += 2) {
		ht_insert(hashTable, &hashData[i], &hashData[i]);
	}

	printf("Size after insertions: %d\n", hashTable->size);

	for (int i = 0; i < 60; i += 2) {
		ht_delete(hashTable, &hashData[i]);
	}

	printf("Size after deletions: %d\n", hashTable->size);


	delete_hashtable(hashTable);

	return 0;

}