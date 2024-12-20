#include"vector.h"

int main(void)
{
    vector* int_vec = newVector(sizeof(int), 0);
    vector* float_vec = newVector(sizeof(float), 0);
    vector* char_vec = newVector(sizeof(char), 0);

    char chars[5] = {'A', 'B', 'C', 'D', 'E'};

    for(int i = 0; i < 5; i++)
    {
        append(int_vec, &i);
        float val = (float) i * 0.2;
        append(float_vec, &val);
        append(char_vec, &chars[i]);
    }

    for(int i = 0; i < 5; i++)
    {
        printf("int_vec[%d]: %d, float_vec[%d]: %f, char_vec[%d]: %c\n",
                i, _get(int, int_vec, i), 
                i, _get(float, float_vec, i), 
                i, *((char*)get(char_vec, i)));
    }
}