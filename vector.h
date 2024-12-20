#ifndef VECTOR_H
#define VECTOR_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define _get(type, vector, index) *((type*)get(vector, index))

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
}vector;

vector* newVector(size_t data_size, size_t initial_capacity);

void append(vector* vec, void* value);
void insert(vector* vec, void* value, size_t index);

void pop(vector* vec);
void delete_element(vector* vec, size_t index);

void* get(vector* vec, size_t index);
void destroy(vector* vec);

#endif