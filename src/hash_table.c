#include "hash_table.h"

//Internal function
static struct ht_item* new_hashtable_item(const char* k, const char* v) {
	struct ht_item* newItem = malloc(sizeof(struct ht_item));
	newItem->key = strdup(k);
	newItem->value = strdup(v);

	return newItem;
}

static ht_hash_table* ht_new_sized(const int base_size) {
	ht_hash_table* ht = malloc(sizeof(ht_hash_table));

	ht->base_size = base_size;
	ht->size = next_prime(base_size);
	ht->count = 0;
	ht->items = calloc((size_t)ht->size, sizeof(struct ht_item*));

	return ht;
}

//Called externally
ht_hash_table* new_hashtable() {
	return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_resize(ht_hash_table* ht, const int new_base_size) {
	if (new_base_size < HT_INITIAL_BASE_SIZE) {
		return;
	}

	ht_hash_table* new_ht = ht_new_sized(new_base_size);

	for (int i = 0; i < ht->size; i++) {
		struct ht_item* current_item = ht->items[i];
		if (current_item != NULL && current_item != &HT_DELETED_ITEM) {
			ht_insert(new_ht, current_item->key, current_item->value);
		}
	}

	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;

	int temp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = temp_size;

	struct ht_item** tempItems = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tempItems;

	delete_hashtable(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
	ht_resize(ht, ht->size * 2);
}

static void ht_resize_down(ht_hash_table* ht) {
	ht_resize(ht, ht->size / 2);
}

static void delete_hashtable_item(struct ht_item* i) {
	free(i->key);
	free(i->value);
	free(i);
}

void delete_hashtable(ht_hash_table* ht) {
	for (int i = 0; i < ht->size; i++) {
		struct ht_item* item = ht->items[i];
		if (item != NULL) {
			delete_hashtable_item(item);
		}
	}

	free(ht->items);
	free(ht);
}

static int ht_hash(const char* s, const int a, const int m) {
	long hash = 0;
	const int string_len = strlen(s);

	for (int i = 0; i < string_len; i++) {
		hash += (long)pow(a, string_len - (i + 1)) * s[i];
		hash = hash % m;
	}

	return (int)hash;
}

static int ht_get_hash(const char* s, const int bucket_count, const int attempt) {
	const int hash_a = ht_hash(s, HT_PRIME_1, bucket_count);
	const int hash_b = ht_hash(s, HT_PRIME_2, bucket_count);
	return (hash_a + (attempt * (hash_b + 1))) % bucket_count;
}

void ht_insert(ht_hash_table* ht, char* a_key, char* a_value) {
	struct ht_item* item = new_hashtable_item(a_key, a_value);

	int index = ht_get_hash(item->key, ht->size, 0);

	struct ht_item* current_item = ht->items[index];
	int i = 1;
	while (current_item != NULL) {
		//If an item exists with the same key that is inserted, the new item replaces it
		if (current_item != &HT_DELETED_ITEM) {
			if (strcmp(current_item->key, a_key) == 0) {
				delete_hashtable_item(current_item);
				ht->items[index] = item;
				return;
			}
		}
		index = ht_get_hash(item->key, ht->size, i);
		current_item = ht->items[index];
		i++;
	}
	ht->items[index] = item;
	ht->count++;

	int load = (ht->count * 100) / ht->size;

	if (load > 70) {
		ht_resize_up(ht);
	}

}

char* ht_search(ht_hash_table* ht, const char* key) {
	int index = ht_get_hash(key, ht->size, 0);
	struct ht_item* item = ht->items[index];
	int i = 1;

	while (item != NULL) {
		if (item != &HT_DELETED_ITEM && strcmp(item->key, key) == 0) {
			return item->value;
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}

	return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key) {
	int index = ht_get_hash(key, ht->size, 0);
	struct ht_item* item = ht->items[index];
	int i = 1;

	while (item != NULL) {
		if (item != &HT_DELETED_ITEM) {
			if (strcmp(item->key, key) == 0) {
				delete_hashtable_item(item);
				ht->items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;

	int load = (ht->count * 100) / ht->size;

	if (load < 10) {
		ht_resize_down(ht);
	}
}
