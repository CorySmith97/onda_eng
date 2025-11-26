#include <stdio.h>

// Header Includes
#include "core/core_inc.h"
#include "platform/platform.h"
#include "engine/engine.h"

// C Includes
#include "core/c_main.c"
#include "platform/platform.c"
#include "engine/engine.c"

void frame() {
    if (isKeyPressed(32)) {
        load_spritesheet("path.zig");
        printf("Key pressed. \n");
    }
}

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

int main() {
    app_run(&(PlatformDesc){
            .title = "test 2",
            .backend = BACKEND_SOKOL_NATIVE,
            .frame_fn = frame,
    });
}

