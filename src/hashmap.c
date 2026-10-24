/**
 * @file hashmap.c
 * @author Amar Campbell
 * @brief This is the hashmap Implementation file
 * @copyright Copyright (c) 2026 Amar
 */

#include "hashmap.h"
#include <string.h>

/**
 * @brief hash the key and return bucket index
 *
 * @param cap
 * @param map pointer to the map
 * @param key the string key to be hashed
 * @return size_t the bucket index in the map
 */
static size_t map_hash(size_t cap, const char* key) {

    if (key == NULL) {
        LOG_ERROR("The key is null");
        return (SIZE_MAX);
    }

    size_t bucket_idx = 0;
    size_t factor     = 31;
    size_t key_length = strlen(key);
    for (size_t i = 0; i < key_length; i++) {
        bucket_idx = ((bucket_idx % cap) + ((((size_t)(unsigned char)key[i]) * factor) % cap)) % cap;

        factor = ((factor % INT16_MAX) * (31 % INT16_MAX)) % INT16_MAX;
    }
    return bucket_idx;
}

MapPtr map_create(const size_t cap, const size_t element_size, MAP_ERROR_CODES* err) {
    if (err == NULL) {
        LOG_ERROR("The err is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return NULL;
    }
    MapPtr map = (MapPtr)calloc(1, sizeof(Map));
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        *err = MAP_ERROR_RETURN_ERROR;

        return NULL;
    }

    map->length = 0;
    if (cap == 0) {
        map->capacity = 100;
    } else {
        map->capacity = cap;
    }
    map->element_size = element_size;
    map->buckets      = (void**)calloc(map->capacity, sizeof(void*));
    if (map->buckets == NULL) {
        LOG_ERROR("The map->buckets is null");
        free(map);
        *err = MAP_ERROR_RETURN_ERROR;
        return NULL;
    }
    *err = MAP_ERROR_RETURN_SUCCESS;
    return map;
}

MAP_ERROR_CODES map_put( MapPtr map, const char* key, const void* value) {
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    if (key == NULL) {
        LOG_ERROR("The key is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    if (value == NULL) {
        LOG_ERROR("The value is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    if (map->length != 0 && ((float)map->length) / (float)map->capacity >= LOAD_FACTOR) {
        MAP_ERROR_CODES error = map_resize(map, map->capacity * 2);

        if (error == MAP_ERROR_RETURN_ERROR) {
            LOG_ERROR("There was an error resizing map capacity");
            return error;
        }
    }

    NodePtr new_node = calloc(1, sizeof(Node));
    if (new_node == NULL) {
        LOG_ERROR("The new_node is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    void* new_key = malloc(strlen(key) + 1);
    if (new_key == NULL) {
        LOG_ERROR("The new_key is null");
        free(new_node);
        return MAP_ERROR_RETURN_ERROR;
    }
    strcpy_s(new_key, strlen(key) + 1, key);
    new_node->key = new_key;

    void* new_value = calloc(1, map->element_size);
    if (new_value == NULL) {
        LOG_ERROR("The new_value is null");
        free(new_node->key);
        free(new_node);
        return MAP_ERROR_RETURN_ERROR;
    }
    memcpy_s(new_value, map->element_size, value, map->element_size);
    new_node->value = new_value;
    new_node->next  = NULL;

    size_t bucket_idx = map_hash(map->capacity, new_node->key);

    if (map->buckets[bucket_idx] == NULL) {
        map->buckets[bucket_idx] = new_node;
        map->length++;
        return MAP_ERROR_RETURN_SUCCESS;
    }

    NodePtr previous = NULL;
    NodePtr current  = map->buckets[bucket_idx];
    while (true) {
        if (current != NULL && strcmp(current->key, new_key) != 0) {
            previous = current;
            current  = current->next;
            continue;
        }

        if (current != NULL && strcmp(new_key, current->key) == 0) {
            free(current->value);
            current->value = new_value;
            free(new_key);
            free(new_node);
            break;
        }

        current        = new_node;
        previous->next = current;
        map->length++;
        break;
    }

    return MAP_ERROR_RETURN_SUCCESS;
}

void* map_get(const Map* map, const char* key, MAP_ERROR_CODES* err) {
    if (err == NULL) {
        LOG_ERROR("The err is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return NULL;
    }

    if (map == NULL) {
        LOG_ERROR("The Map is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return NULL;
    }

    if (key == NULL) {
        LOG_ERROR("The key is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return NULL;
    }

    size_t bucket_idx = map_hash(map->capacity, key);
    if (bucket_idx >= map->capacity) {
        *err = MAP_ERROR_OUT_OF_BOUND;
        return NULL;
    }

    if (map->buckets[bucket_idx] == NULL) {
        *err = MAP_ERROR_EMPTY_BUCKET;
        return NULL;
    }

    NodePtr current = ((NodePtr)map->buckets[bucket_idx]);

    while (true) {
        if (current != NULL && strcmp(current->key, key) == 0) {
            break;
        }

        if (current != NULL && strcmp(current->key, key) != 0) {
            current = current->next;
            continue;
        }

        *err = MAP_ERROR_NOT_FOUND;
        return NULL;
    }

    *err = MAP_ERROR_RETURN_SUCCESS;
    return current->value;
}

MAP_ERROR_CODES map_remove(MapPtr map, const char* key) {
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    if (key == NULL) {
        LOG_ERROR("The key is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    size_t bucket_idx = map_hash(map->capacity, key);

    if (bucket_idx >= map->capacity) {
        return MAP_ERROR_OUT_OF_BOUND;
    }

    NodePtr previous = NULL;
    NodePtr current  = map->buckets[bucket_idx];
    if (current == NULL) {
        return MAP_ERROR_NOT_FOUND;
    }

    while (current != NULL) {
        NodePtr next = current->next;
        if (strcmp(current->key, key) == 0 && previous == NULL) {
            free(current->key);
            free(current->value);
            free(current);
            map->buckets[bucket_idx] = next;
            map->length--;
            return MAP_ERROR_RETURN_SUCCESS;
        }

        if (strcmp(current->key, key) == 0) {
            free(current->key);
            free(current->value);
            previous->next = next;
            free(current);
            map->length--;
            return MAP_ERROR_RETURN_SUCCESS;
        }
        previous = current;
        current  = next;
    }

    return MAP_ERROR_NOT_FOUND;
}

bool map_contains(const Map* map, const char* key, MAP_ERROR_CODES* err) {
    if (err == NULL) {
        LOG_ERROR("The err is null");
        return false;
    }
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return false;
    }

    if (key == NULL) {
        LOG_ERROR("The key is null");
        *err = MAP_ERROR_RETURN_ERROR;
        return false;
    }

    size_t bucket_idx = map_hash(map->capacity, key);

    if (bucket_idx >= map->capacity) {
        *err = MAP_ERROR_OUT_OF_BOUND;

        return false;
    }

    if (map->length == 0) {
        *err = MAP_ERROR_NOT_FOUND;
        return false;
    }

    NodePtr current = (NodePtr)map->buckets[bucket_idx];

    while (true) {
        if (current == NULL) {
            *err = MAP_ERROR_NOT_FOUND;
            return false;
        }

        if (strcmp(current->key, key) == 0) {
            break;
        }

        current = current->next;
    }

    *err = MAP_ERROR_RETURN_SUCCESS;
    return true;
}

MAP_ERROR_CODES map_resize(MapPtr map, size_t new_cap) {
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    size_t new_cap_t;
    if (new_cap == 0 || new_cap == map->capacity) {
        new_cap_t = map->capacity * 2;
    } else {
        new_cap_t = new_cap;
    }

    auto  const new_buckets = (void**)calloc(new_cap_t, sizeof(void*));
    if (new_buckets == NULL) {
        LOG_ERROR("The new_buckets is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        NodePtr map_bucket_current = map->buckets[i];

        while (map_bucket_current != NULL) {
             size_t bucket_idx               = map_hash(new_cap_t, map_bucket_current->key);
            NodePtr map_bucket_current_next = map_bucket_current->next;

            if (new_buckets[bucket_idx] == NULL) {
                map_bucket_current->next = NULL;
                new_buckets[bucket_idx]  = map_bucket_current;
                map_bucket_current       = map_bucket_current_next;
                continue;
            }

            NodePtr new_bucket_previous = NULL;
            NodePtr new_bucket_current  = ((NodePtr)new_buckets[bucket_idx]);
            while (true) {

                if (new_bucket_current == NULL) {
                    map_bucket_current->next  = NULL;
                    new_bucket_current        = map_bucket_current;
                    new_bucket_previous->next = new_bucket_current;
                    break;
                }
                new_bucket_previous = new_bucket_current;
                new_bucket_current  = new_bucket_previous->next;
            }
            map_bucket_current = map_bucket_current_next;
        }
    }

    free((void*)map->buckets);
    map->buckets  = new_buckets;
    map->capacity = new_cap_t;

    return MAP_ERROR_RETURN_SUCCESS;
}

static inline void map_free_buckets(MapPtr map) {

    for (size_t i = 0; i < map->capacity; i++) {
        NodePtr current = map->buckets[i];

        while (current != NULL) {
            NodePtr next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
        map->buckets[i] = NULL;
    }
}

MAP_ERROR_CODES map_clear(MapPtr map) {
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    map_free_buckets(map);
    map->length = 0;

    return MAP_ERROR_RETURN_SUCCESS;
}

MAP_ERROR_CODES map_free(MapPtr map) {
    if (map == NULL) {
        LOG_ERROR("The Map is null");
        return MAP_ERROR_RETURN_ERROR;
    }

    map_free_buckets(map);
    free((void*)map->buckets);
    free(map);

    return MAP_ERROR_RETURN_SUCCESS;
}
