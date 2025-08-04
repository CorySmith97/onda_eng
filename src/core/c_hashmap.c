//
// Created by Cory Smith on 8/3/25.
//

#include "core.h"

Hashmap *hashmap_create(
    Arena *arena
) {}

void hashmap_free(
    Hashmap *map
) {}

void hashmap_set(
    Hashmap *map,
    String8 key,
    void *value
) {}

void *hashmap_get(
    Hashmap *map,
    String8 *key
) {}

void hashmap_remove(
    Hashmap *map,
    String8 *key
) {}
