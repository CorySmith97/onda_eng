// @todo:cs this needs to be rewritten to use Arenas.
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }
    return hash % TABLE_SIZE;
}

// Create a new hashmap
HashMap* hashmap_create(size_t stride) {
    HashMap *map = malloc(sizeof(HashMap));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->buckets[i] = NULL;
    }
    map->stride = stride;
    return map;
}

// Insert or update a key-value pair
void hashmap_put(HashMap *map, const char *key, void *value) {
    unsigned int index = hash(key);
    Entry *entry = map->buckets[index];

    // Check if key already exists
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // Update existing value
            memcpy(entry->value, value, map->stride);
            return;
        }
        entry = entry->next;
    }

    // Create new entry
    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = malloc(map->stride);
    memcpy(new_entry->value, value, map->stride);
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
}

// Get a value by key
void* hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = map->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;  // Key not found
}

// Remove a key-value pair
void hashmap_remove(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    Entry *entry = map->buckets[index];
    Entry *prev = NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                map->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// Free the hashmap
void hashmap_destroy(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = map->buckets[i];
        while (entry != NULL) {
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(map);
}

