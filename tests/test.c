#include "../src/hash_table.h"

//Compile command: gcc test.c ../src/hash_table.c ../src/prime_generator.c

int main() {

	ht_hash_table* hashTable = new_hashtable();

	ht_insert(hashTable, "A", "Alpha");
	ht_insert(hashTable, "B", "Beta");
	ht_insert(hashTable, "G", "Gamma");

	const char* item1 = ht_search(hashTable, "A");
	const char* item2 = ht_search(hashTable, "B");
	const char* item3 = ht_search(hashTable, "G");

	printf("%s\n", item1);
	printf("%s\n", item2);
	printf("%s\n", item3);

	return 0;
}