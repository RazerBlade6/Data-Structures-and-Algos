#ifndef HASH_TABLE_V
#define HASH_TABLE_V

#define TABLE_CAPACITY 17
#define HASH_CONST 33

#include <stddef.h>
#include "utils.h"

typedef struct HASH_TABLE_ENTRY {
    const char *key;
    void *value;
} ht_entry_t;

typedef struct ENTRY_NODE node_t;

struct ENTRY_NODE {
    ht_entry_t entry;
    node_t *next;
};

typedef struct HASH_TABLE {
    node_t **entries;
    size_t capacity;
    size_t length;
} hash_table_t;

hash_table_t* init_hash_table(void);

node_t* init_node(const char *key, void *value);

uint64_t hash_key(const char *key, size_t capacity);

const char* hash_table_insert(hash_table_t *table, const char* key, void* value);

void* hash_table_find(hash_table_t *table, const char *key);

void* hash_table_delete(hash_table_t *table, const char *key);

void hash_table_display(hash_table_t *table);

void hash_table_destroy(hash_table_t *table);
#endif