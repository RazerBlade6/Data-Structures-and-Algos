#include "include/hashtable.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    hash_table_t *table = init_hash_table();

    hash_table_insert(table, "google.com", "172.217.12.14");
    hash_table_insert(table, "youtube.com", "216.58.192.206");
    hash_table_insert(table, "amazon.com", "176.32.103.205");
    hash_table_insert(table, "wikipedia.org", "91.198.174.192");
    hash_table_insert(table, "netflix.com", "45.57.65.72");
    hash_table_insert(table, "linkedin.com", "108.174.10.10");
    hash_table_insert(table, "reddit.com", "151.101.65.140");
    hash_table_insert(table, "microsoft.com", "40.76.4.15");
    hash_table_insert(table, "primevideo.com", "52.205.93.218");
    hash_table_insert(table, "github.com", "151.101.64.84");
    hash_table_insert(table, "steamcommunity.com", "199.181.132.250");
    hash_table_insert(table, "abcdefg.in", "123.45.67.890");
    hash_table_insert(table, "helloworld.com", "111.112.323.4");
    
    puts("Welcome to the Hash Table Interface");
    while (true) {
        char *choice = calloc(255, sizeof(char));
        char *key = calloc(255, sizeof(char));
        char *value = calloc(255, sizeof(char));

        puts("\n0. Clear the Screen\n1. Enter Hostname with IP\n2. Display the Table\n3. Find an IP by domain\n4. Delete a Value from the Table\n5. Exit");
        printf("Enter Your Choice: ");
        
        get_string(choice);

        if (!validate_uint(choice)) {
            puts("Invalid Input\n");
            continue;
        }
        
        switch(atoi(choice)) {
            case 0: system("cls"); break;
            case 1:
                printf("Enter the Domain: ");
                get_string(key);
                printf("Enter the IP Address: ");
                get_string(value);
                hash_table_insert(table, key, value);
                puts("\n");
                break;
            case 2:
                hash_table_display(table);
                break;
            case 3:
                printf("Enter the Domain: ");
                get_string(key);
                void *value = hash_table_find(table, key);
                if (!value) {
                    puts("Key not found");
                } else {
                    printf("{`%s`: `%s`} found in the Table\n", key, (char *)value);
                }
                puts("\n");
                break;
            case 4:
                printf("Enter a key: ");
                get_string(key);
                void *deleted = hash_table_delete(table, key);
                if (deleted == NULL) {
                    puts("Key not found");
                } else {
                    printf("{`%s`: `%s`} deleted from the table", key, (char *)deleted);
                }
                puts("\n");
                break;
            case 5:
                hash_table_destroy(table);
                free(key);
                free(value);
                return 0;
            default:
                puts("Invalid Choice");
        }
    }
    

    return 0;
}

hash_table_t* init_hash_table(void) {
    hash_table_t *table = malloc(sizeof(hash_table_t));

    if (table == NULL) {
        perror("Error");
        return NULL;
    }

    table->capacity = TABLE_CAPACITY;
    table->length = 0;
    table->entries = (node_t **)calloc(table->capacity, sizeof(node_t*));

    if (table->entries == NULL) {
        perror("Error");
        free(table);
        return NULL;
    }

    for (int i = 0; i < TABLE_CAPACITY; i++) {
        table->entries[i] = calloc(1, sizeof(node_t));
        if (table->entries[i] == NULL) {
            perror("Error");
            free(table->entries);
            free(table);
            return NULL;
        }

        table->entries[i]->next = calloc(1, sizeof(node_t));
        if (table->entries[i]->next == NULL) {
            perror("Error");
            free(table->entries);
            free(table);
            return NULL;
        }

        table->entries[i]->next = NULL;
    }

    return table;
}

node_t* init_node(const char *key, void *value) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        perror("Error");
        return NULL;
    }
    node->entry.key = key;
    node->entry.value = value;
    node->next = NULL;

    return node;
}

const char* hash_table_insert(hash_table_t *table, const char* key, void* value) {

    if (table->length == table->capacity - 1) {
        printf("Hash Table is Full\n");
        return NULL;
    }
    uint64_t index = hash_key(key, table->capacity);
    table->length++;
    node_t *node = init_node(key, value);

    if (table->entries[index]->entry.key == NULL) {
        table->entries[index] = node;
        return key;
    }

    node_t *current = table->entries[index];

    if (strcmp(current->entry.key, key) == 0) {
        current->entry.value = value;
        return current->entry.key;
    }

    while(current->next != NULL) {
        if (strcmp(current->entry.key, key) == 0) {
            current->entry.value = value;
            return current->entry.key;
        }
        current = current->next;
    }
    current->next = node;

    return key;
}

uint64_t hash_key(const char *key, size_t capacity) {
    size_t length = strlen(key);
    uint64_t a = 1;
    uint64_t hash = 0;

    for (uint64_t i = 0; i < length; i++) {
        hash += key[i] * a;
        a *= HASH_CONST;
    }
    hash = hash % capacity;
    return hash;
}

void hash_table_display(hash_table_t *table) {
    puts("\n\nHASH TABLE: \n");

    for (uint64_t i = 0; i < table->capacity; i++) {
        node_t *current = table->entries[i];
        if (current->entry.key == NULL)
            continue;
        
        printf("%lld. ", i);
        while(current->next != NULL) {
            printf("{`%s`: `%s`} -> ", current->entry.key, (char *)current->entry.value);
            current = current->next;
        }
        printf("{`%s`: `%s`}\n", current->entry.key, (char *)current->entry.value);
    }
    
    puts("\n");
}

void* hash_table_find(hash_table_t *table, const char *key) {
    uint64_t index = hash_key(key, table->capacity);

    node_t *current = table->entries[index];
    if (current->entry.key == NULL) 
        return NULL;

    while(current != NULL) {
        if (strcmp(current->entry.key, key) == 0)
            return current->entry.value; 
        current = current->next;
    }
    return NULL;
}

void* hash_table_delete(hash_table_t *table, const char *key) {
    uint64_t index = hash_key(key, table->capacity);

    node_t *current = table->entries[index];
    if (current == NULL) {
        return NULL;
    }

    if (strcmp(current->entry.key, key) == 0) {
        void *ret = current->entry.value;
        table->entries[index] = current->next;
        free(current);
        return ret;
    }

    node_t *prev;
    while (current != NULL) {
        prev = current;
        current = current->next;

        if (strcmp(current->entry.key, key) == 0) {
            void *ret = current->entry.value;
            prev->next = current->next;
            free(current);
            return ret;
        }
    }

    return NULL;
}

void hash_table_destroy(hash_table_t *table) {
    for (uint64_t i = 0; i < table->capacity; i++) {
        node_t *current = table->entries[i];
        node_t *next;
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        free(table->entries[i]);
    }
    free(table->entries);
    free(table);
}