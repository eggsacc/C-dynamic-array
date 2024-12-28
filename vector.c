#include "vector.h"

/* 
 * @brief Creates & initializes a new vector.
 * @param[in] size_t data_size
 * @param[in] size_t initial_capacity
 * @return cvector* 
 */
cvector* CreateVector(size_t data_size, size_t initial_capacity)
{
    /* Default capacity is 8 bytes */
    initial_capacity = initial_capacity ? initial_capacity : 8;

    /* Malloc for vector metadata & check if successful */
    cvector* vec = malloc(sizeof(cvector));
    if(vec == NULL)
    {
        printf("ERROR: CreateVector(): struct malloc fail\n");
        return NULL;
    }

    /* Malloc for vector data array & check if successful */
    void* temp = malloc(data_size * initial_capacity);
    if(temp == NULL)
    {
        printf("ERROR: CreateVector(): array malloc fail\n");
        return NULL;
    }

    /* Initialize members */
    vec->array = temp;
    vec->capacity = initial_capacity;
    vec->data_size = data_size;
    vec->size = 0;
    return vec;
}

/*
 * @brief Append new value to end of vector.
 * @param[in] cvector* vec
 * @param[in] void* value
 * @note Typecast value pointer to void*
 */
void cvector_append(cvector* vec, void* value)
{
    /* Check if vector requires resizing */
    if(vec->size == vec->capacity)
    {
        /* Realloc twice the current capacity */
        vec->capacity *= 2;
        void* temp = realloc(vec->array, vec->capacity * vec->data_size);
        if(temp == NULL)
        {
            printf("ERROR: cvector_append(): realloc fail\n");
            return;
        }
        vec->array = temp;
    }

    /* Copy data from value pointer into end of vector */
    memcpy((char*)vec->array + (vec->size * vec->data_size), value, vec->data_size);

    /* Update vector size */
    vec->size++;
}

/* 
 * @brief Inserts a value at requested index.
 * @param[in] cvector* vec
 * @param[in] void* value
 * @param[in] size_t index
 * @note Typecast value pointer to void*
 */
void cvector_insert(cvector* vec, void* value, size_t index)
{
    /* Check if insertion index is beyond contiguous range */
    if(index > vec->size)
    {
        printf("ERROR: cvector_insert(): insertion beyond array size\n");
        return;
    }

    /* Check if vector requires resizing */
    if(vec->size == vec->capacity)
    {
        /* Realloc twice the current capacity */
        vec->capacity *= 2;
        void* temp = realloc(vec->array, vec->capacity);

        if(temp == NULL)
        {
            printf("ERROR: cvector_insert(): realloc fail\n");
            return;
        }
        vec->array = temp;
    }

    /* Shift elements after index up by 1 position */
    memmove((char*)vec->array + ((index + 1) * vec->data_size), 
            (char*)vec->array + (index * vec->data_size),
            (vec->size - index)*vec->data_size);
          
    /* Copy data from value pointer to index address */
    memcpy((char*)vec->array + (index * vec->data_size), value, vec->data_size);
    vec->size++;
}

/*
 * @brief Returns & deletes last element in vector.
 * @param[in] cvector* vec
 * @return void* data
 * @note Returns NULL if list empty.
 * @warning Free returned data pointer after use.
 */
void* cvector_pop(cvector* vec)
{
    /* Check if vector is empty */
    if(vec->size <= 0)
    {
        printf("WARNING: cvector_pop(): list empty\n");
        return NULL;
    }
    
    /* Extract last element data and set to NULL */
    void* return_data = malloc(vec->data_size);
    void* vector_end_address = (void*)((char*)vec->array + (vec->size - 1) * vec->data_size);
    memcpy(return_data, vector_end_address, vec->data_size);
    memset(vector_end_address, 0, vec->data_size);

    /* Updatee vector size */
    vec->size--;
    return return_data;
}

/*
 * @brief Returns & deletes element at index.
 * @param[in] cvector* vec
 * @param[in] size_t index
 * @return void* data
 * @note Returns NULL if list empty.
 * @warning Free returned data pointer after use.
 */
void* cvector_delete(cvector* vec, size_t index)
{
    /* Check if index is within vector size */
    if(index >= vec->size)
    {
        printf("ERROR: cvector_delete(): index out of range\n");
        return NULL;
    }

    /* Extract element data */
    void* return_data = malloc(vec->data_size);
    void* element_index_address = (void*)((char*)vec->array + (index * vec->data_size));
    memcpy(return_data, element_index_address, vec->data_size);

    /* Move all elements after index 1 position down to overwrite it */
    memmove(element_index_address, 
            (char*)vec->array + ((index + 1) * vec->data_size),
            vec->data_size * (vec->size - index - 1));

    // Update array size
    vec->size--;

    return return_data;
}

/*
 * @brief Access data at index
 * @param[in] cvector* vec
 * @param[in] size_t index
 * @return void* data
 * @note Returns NULL if index is invalid.
 * @warning DO NOT free returned pointer after use.
 */
void* cvector_get(cvector* vec, size_t index)
{
    /* Check if index is within vector size */
    if(index >= vec->size)
    {
        printf("ERROR: get(): index[%d] outside array size[%d]\n", index, vec->size - 1);
        return NULL;
    }

    /* Return pointer to data */
    return (char*)vec->array + (index * vec->data_size);
}

/* 
 * @brief De-initializes cvector.
 * @param[in] cvector* vec
 * @warning Only to be called at end of program.
 */
void cvector_destroy(cvector* vec)
{
    /* Only free if vector is not empty */
    if(vec != NULL && vec->array != NULL)
    {
        free(vec->array);
        vec->array = NULL;
        free(vec);
        vec = NULL;
    }
}
