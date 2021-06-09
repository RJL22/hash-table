#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "prime_generator.h"

#define HT_INITIAL_BASE_SIZE 50

#define HT_PRIME_1 97
#define HT_PRIME_2 193

struct ht_item {
	char* key;
	char* value;
};

static struct ht_item HT_DELETED_ITEM = {NULL, NULL};

typedef struct {
	int base_size;
	int size;
	int count;
	struct ht_item** items;
} ht_hash_table;

//Methods for hashtable creation and deletion
ht_hash_table* new_hashtable();
void delete_hashtable();

//Methods for hashtable management
void ht_insert(ht_hash_table* ht, char* key, char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);

