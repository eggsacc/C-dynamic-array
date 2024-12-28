#include"vector.h"

int main(void)
{
    cvector* int_vec = CreateVector(sizeof(int), 0);
    cvector* float_vec = CreateVector(sizeof(float), 0);
    cvector* char_vec = CreateVector(sizeof(char), 0);

    char chars[3] = {'A', 'B', 'C'};

    /* Assign values to vectors */
    for(int i = 0; i < 3; i++)
    {
        cvector_append(int_vec, (void*)&i);
        float val = (float) i * 3.1415;
        cvector_append(float_vec, (void*)&val);
        cvector_append(char_vec, (void*)&chars[i]);
    }
    printf("int_vec capacity: %d\n", int_vec->capacity);
    printf("float_vec capacity: %d\n", float_vec->capacity);
    printf("char_vec capacity: %d\n", char_vec->capacity);

    /* Print out elements in each vector */
    for(int i = 0; i < int_vec->size; i++)
    {
        printf("int_vec[%d]: %d, float_vec[%d]: %f, char_vec[%d]: %c\n",
                i, *((int*)cvector_get(int_vec, i)), 
                i, cvector_get_type(float_vec, i, float), 
                i, cvector_get_type(char_vec, i, char));
    }

    /* Insert more elements */
    for(int i = 0; i < 32; i++)
    {
        cvector_append(int_vec, (void*)&i);
        float val = (float) i;
        cvector_append(float_vec, (void*)&val);
        cvector_append(char_vec, (void*)&chars[i%3]);
    }
    printf("----------------After inserting 32 new items----------------\n");
    printf("New int_vec capacity: %d\n", int_vec->capacity);
    printf("New float_vec capacity: %d\n", float_vec->capacity);
    printf("New char_vec capacity: %d\n", char_vec->capacity);

    printf("----------------Pop/delete functions----------------\n");

    printf("Current int_vec size: %d\n", int_vec->size);
    printf("Current float_vec size: %d\n", float_vec->size);
    /* pop int_vector */
    printf("Last element in int_vec: %d\n", *((int*)cvector_pop(int_vec)));
    printf("New int_vec size: %d\n", int_vec->size);

    /* Delete element at index [1] from float_vec */
    printf("Element at index[1] in float_vec: %f\n", cvector_delete_type(float_vec, 1, float));
    printf("New float_vec size: %d\n", float_vec->size);

    /* Destroy vectors */
    cvector_destroy(int_vec);
    cvector_destroy(float_vec);
    cvector_destroy(char_vec);

}