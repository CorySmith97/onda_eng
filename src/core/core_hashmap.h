#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
// Example usage
int main() {
    // Example 1: HashMap of integers
    HashMap *int_map = hashmap_create(sizeof(int));

    int age = 30;
    int score = 95;
    hashmap_put(int_map, "age", &age);
    hashmap_put(int_map, "score", &score);

    int *retrieved_age = (int*)hashmap_get(int_map, "age");
    printf("age: %d\n", *retrieved_age);

    // Example 2: HashMap of structs
    typedef struct {
        float x;
        float y;
    } Point;

    HashMap *point_map = hashmap_create(sizeof(Point));

    Point p1 = {10.5, 20.3};
    Point p2 = {5.0, 15.7};
    hashmap_put(point_map, "origin", &p1);
    hashmap_put(point_map, "destination", &p2);

    Point *retrieved_point = (Point*)hashmap_get(point_map, "origin");
    printf("origin: (%.1f, %.1f)\n", retrieved_point->x, retrieved_point->y);

    // Example 3: HashMap of strings (char pointers)
    HashMap *str_map = hashmap_create(sizeof(char*));

    char *name = "Alice";
    char *city = "New York";
    hashmap_put(str_map, "name", &name);
    hashmap_put(str_map, "city", &city);

    char **retrieved_name = (char**)hashmap_get(str_map, "name");
    printf("name: %s\n", *retrieved_name);

    // Clean up
    hashmap_destroy(int_map);
    hashmap_destroy(point_map);
    hashmap_destroy(str_map);

    return 0;
}
*/
