/**
 * @file hashmap.h
 * @author Amar Campbell
 * @brief This is the hashmap declaration header file
 * @copyright Copyright (c) 2026 Amar
 */
#ifndef INCLUDED_HASHMAP
#define INCLUDED_HASHMAP
#include <stddef.h>
#define LOAD_FACTOR 0.75

typedef enum {
    MAP_ERROR_RETURN_SUCCESS,
    MAP_ERROR_RETURN_ERROR,
    MAP_ERROR_NOT_FOUND,
    MAP_ERROR_OUT_OF_BOUND,
    MAP_ERROR_EMPTY_BUCKET
} MAP_ERROR_CODES;

struct map {
    size_t element_size;
    size_t length;
    size_t capacity;
    void** buckets;
};

struct node {
    char* key;
    void* value;
    void* next;
};

typedef struct map Map;
typedef Map* MapPtr;
typedef struct node Node;
typedef Node* NodePtr;

/**
 * @brief Create the map
 *
 * @param cap The number of buckets in the map
 * @return pointer to map
 */
MapPtr map_create(size_t cap, size_t element_size);

/**
 * @brief add a node in the map
 * 
 * @param map Pointer to the map
 * @param key the skey for the value
 * @param value the value to add
 * @return MAP_ERROR_CODES the enum error codes
 */
MAP_ERROR_CODES map_put(MapPtr map,  const char* key, const void* value);

/**
 * @brief get the value base on the key
 * 
 * @param map Pointer to the map
 * @param key the key of the value in the map
 * @return void* pointer to the value 
 */
void* map_get(MapPtr map, const char * key);

/**
 * @brief remove the node with that key
 *
 * @param map Pointer to the 
 * @param key
 * @return MAP_ERROR_CODES the enum error codes
 */
MAP_ERROR_CODES map_remove(MapPtr map, const char* key);
#endif
