#define TABLE_SIZE 1000

typedef struct Entry {
    char *key;
    void *value;
    struct Entry *next;
} Entry;

// HashMap structure
typedef struct HashMap {
    Entry *buckets[TABLE_SIZE];
    size_t stride;
} HashMap;

HashMap* hashmap_create(size_t stride);
void hashmap_put(HashMap *map, const char *key, void *value);
void* hashmap_get(HashMap *map, const char *key);
void hashmap_remove(HashMap *map, const char *key);
void hashmap_destroy(HashMap *map);
size_t hashmap_keys(HashMap *map, const char **out_keys, size_t max_keys);
