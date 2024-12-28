#ifndef VECTOR_H
#define VECTOR_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* 
 * Macros to simplify type-casting
 */
#define cvector_get_type(vector, index, type) *((type*)cvector_get(vector, index))
#define cvector_pop_type(vector, type) *((type*)cvector_pop(vector))
#define cvector_delete_type(vector, index, type) *((type*)cvector_delete(vector, index))

/* 
 * Dynamic array struct
 * Stores malloced address (array),
 * malloced capacity,
 * size of each element (to accomodate different datatypes),
 * and number of elements (size)
 */
typedef struct {
    void* array;
    size_t capacity;
    size_t data_size;
    size_t size;
}cvector;

/*
 * Functions
 */
cvector* CreateVector(size_t data_size, size_t initial_capacity);

void cvector_append(cvector* vec, void* value);
void cvector_insert(cvector* vec, void* value, size_t index);

void* cvector_pop(cvector* vec);
void* cvector_delete(cvector* vec, size_t index);

void* cvector_get(cvector* vec, size_t index);

void cvector_destroy(cvector* vec);

#endif