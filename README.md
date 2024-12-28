## Dynamic arrays in C

A simple program to learn about basic memory management and play around with `void` pointers in C, implemented in the form of a variable-sized array.

The dynamic array struct variable is named `cvector` since it sort of resembles a vector in C++.

## `void` pointers

One of the goals of the project was to make the arrays loosely typed, meaning that each array can be of any data type. This was achieved using the `void` pointer, which is a universal pointer with no type associated with it.

## Functions

1) `cvector* CreateVector(size_t data_size, size_t initial_capacity);`
2) `void cvector_append(cvector* vec, void* value);`
3) `void cvector_insert(cvector* vec, void* value, size_t index);`
4) `void* cvector_pop(cvector* vec);`
5) `void* cvector_delete(cvector* vec, size_t index);`
6) `void* cvector_get(cvector* vec, size_t index);`
7) `void cvector_destroy(cvector* vec);`

## Macros

Macros are available for all the functions with a `void*` return type to simplify the type-casting process.

```c
#define cvector_get_type(vector, index, type)    *((type*)cvector_get(vector, index))
#define cvector_pop_type(vector, type)           *((type*)cvector_pop(vector))
#define cvector_delete_type(vector, index, type) *((type*)cvector_delete(vector, index))
```
### Example macro usage

```c
/* Instead of : */
int last_element = *((int*)cvector_pop(int_vector));
/* Using macro: */
int last_element = cvector_pop_type(int_vector, int);
```

