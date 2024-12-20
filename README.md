## Dynamic arrays in C

This was a simple excercise to learn about memory management and play around with `void` pointers in C, creating a basic library that emulates a variable-sized array.

I named the dynamic array variable struct `vector` since it sort of resembles a vector in C++.

## `void` pointers

One of the goals of the project was to make the arrays loosely typed, meaning that each array can be of any data type. This was achieved using the `void` pointer, which is a universal pointer with no type associated with it.

## Macro

There is 1 macro `_get(type, vector, index)` available to simplify the process of type-casting and dereferencing when trying to access an element.

```c
#define _get(type, vector, index) *((type*)get(vector, index))
```
## Example

```c
// Create new vector
vector* int_vec = newVector(sizeof(int), 0);

// Append numbers 0-4 to vector
for(int i = 0; i < 5; i++)
{
  append(int_vec, &i);
}

// Print out each number
for(int i = 0; i < vec->size; i++)
{
  printf("int_vec[%d]: %d", i, *((int*)get(int_vec, i)));

  // Or
  printf("int_vec[%d]: %d", i, ((int*)int_vec->array)[i]);

  //Or
  printf("int_vec[%d]: %d, i, _get(int, int_vec, i));
}
```
Note that any function with a return value always returns a `void` pointer, which has to be type-casted to the element type before de-referencing.
