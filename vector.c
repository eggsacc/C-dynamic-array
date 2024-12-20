#include "vector.h"

/* Creates new vector;
 * allocates memory to the vector struct and data field.
 * If initial array size if unknown, defaults to 8 bytes.
 */
vector* newVector(size_t data_size, size_t initial_capacity)
{
    initial_capacity = initial_capacity ? initial_capacity : 8;
    vector* vec = malloc(sizeof(vector));
    if(vec == NULL)
    {
        printf("ERROR: newVector(): struct malloc fail\n");
        return NULL;
    }
    void* temp = malloc(data_size * initial_capacity);
    if(temp == NULL)
    {
        printf("ERROR: newVector(): array malloc fail\n");
        return NULL;
    }
    vec->array = temp;
    vec->capacity = initial_capacity;
    vec->data_size = data_size;
    vec->size = 0;
    return vec;
}

/*
 * Append a value to the end of vector
 */
void append(vector* vec, void* value)
{
    if(vec->size == vec->capacity)
    {
        vec->capacity *= 2;
        void* temp = realloc(vec->array, vec->capacity * vec->data_size);
        if(temp == NULL)
        {
            printf("ERROR: append(): realloc fail\n");
            return;
        }
        vec->array = temp;
    }
    memcpy((char*)vec->array + (vec->size * vec->data_size), value, vec->data_size);
    vec->size++;
}

/* 
 * Insert value at index 
 */
void insert(vector* vec, void* value, size_t index)
{
    // Check if insertion index is beyond contiguous range
    if(index > vec->size)
    {
        printf("ERROR: insert(): insertion beyond array size\n");
        return;
    }

    // Realloc memory to current * 2 if array size exceeds malloced size
    if(vec->size == vec->capacity)
    {
        vec->capacity *= 2;
        void* temp = realloc(vec->array, vec->capacity);

        if(temp == NULL)
        {
            printf("ERROR: insert(): realloc fail\n");
            return;
        }
        vec->array = temp;
    }

    // Shift all elements from insertion index to end of array up by 1 position
    memmove((char*)vec->array + ((index + 1) * vec->data_size), 
            (char*)vec->array + (index * vec->data_size),
            (vec->size - index)*vec->data_size);
          
    // Copy value from value pointer into array
    memcpy((char*)vec->array + (index * vec->data_size), value, vec->data_size);
    vec->size++;
}

/*
 * Remove last element, decrements size variable so last element is no longer accessible
 */
void pop(vector* vec)
{
    // Check if array is empty
    if(vec->size > 0)
    {
        // Update array size
        vec->size--;
        return;
    }
    printf("WARNING: pop(): list empty\n");
    return;
}

/*
 * Deletes an element at index
 */
void delete_element(vector* vec, size_t index)
{
    // Check if index is outside array range
    if(index >= vec->size)
    {
        printf("ERROR: remove(): index out of range");
        return;
    }

    // Move all elements after index 1 position down to essentially overwrite it
    memmove((char*)vec->array + ((index) * vec->data_size), 
            (char*)vec->array + ((index + 1) * vec->data_size),
            vec->data_size * (vec->size - index - 1));

    // Update array size
    vec->size--;
}

/*
 * Access element in array
 */
void* get(vector* vec, size_t index)
{
    // Check if index to access is outside array length
    if(index >= vec->size)
    {
        printf("ERROR: get(): index[%d] outside array size[%d]\n", index, vec->size - 1);
        return NULL;
    }

    // Return pointer to element address
    return (char*)vec->array + (index * vec->data_size);
}

/* 
 * Destroy (free) dynamic array
 */
void destroy(vector* vec)
{
    if(vec != NULL && vec->array != NULL)
    {
        free(vec->array);
        vec->array = NULL;
        free(vec);
        vec = NULL;
    }
}
