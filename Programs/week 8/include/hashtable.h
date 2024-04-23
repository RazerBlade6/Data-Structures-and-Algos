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

/**
 * A Hash Table that accepts strings as keys and arbitary data as values.
 * @param entries a list of nodes that form the base of the Hash Table.
 * @param capacity the maximum size of the table.
 * @param length the current size of the table.
*/
typedef struct HASH_TABLE {
    node_t **entries;
    size_t capacity;
    size_t length;
} hash_table_t;

/**
 * Initialises the Hash Table. Performs all necessary memory allocations and checks.
*/
hash_table_t* init_hash_table(void);

/**
 * Initialises a single node with a key-value pair.
 * This function is only internal and cannot be called directly.
 * @param key A string to act as the Hash Key.
 * @param value The value to be inserted into the Hash Table.
*/
static node_t* init_node(const char *key, void *value);

/**
 * Polynomial Hashing Function.
 * @param key The string to be hashed.
 * @param capacity The current capacity of the table to be used as modulus.
*/
uint64_t hash_key(const char *key, size_t capacity);

/**
 * Inserts a key-value pair into the table. If the key is already
 * present, the value is updated.
 * @param table The table to be inserted to.
 * @param key The string to act as the Hash Key.
 * @param value The value to be inserted into the Hash Table.
*/
const char* hash_table_insert(hash_table_t *table, const char* key, void* value);

/**
 * Locates and returns a value in the table according to its key. 
 * Returns the value if the key is found. Otherwise returns NULL.
 * @param table The table to be searched.
 * @param key The string to act as the Key.
*/
void* hash_table_find(hash_table_t *table, const char *key);

/**
 * Locates and deletes a key-value pair in the table according to its key. 
 * Returns the value if the key is found. Otherwise returns NULL.
 * @param table The table to be deleted from.
 * @param key The string to act as the Key.
*/
void* hash_table_delete(hash_table_t *table, const char *key);

/**
 * Destroys the Hash Table and frees all allocated memory.
 * Call this to prevent memory leaks.
 * @param table The table to be destroyed.
*/
void hash_table_destroy(hash_table_t *table);

void hash_table_display(hash_table_t *table);
#endif
