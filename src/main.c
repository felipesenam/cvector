#include "vector.h"
#include <stdio.h>

usingVector(int, _int);

void printVector(Vector(_int) * vector)
{
    printf("[");
    printf("%d", *vector->get(vector, 0));
    for (size_t i = 1; i < vector->size; ++i)
        printf(", %d", *vector->get(vector, i));
    printf("]\n");
    printf("[%d ... %d]\n", vector->rseek(vector, vector->size - 1)->value, vector->seek(vector, vector->size - 1)->value);
}

int main(/*int argc, char *argv[]*/)
{
    Vector(_int) vector = DefaultVector(_int);

    // vector.delete = FROM(_int, delete);

    for (int i = 0; i < 25; ++i)
    {
        vector.emplace_front(&vector, i);
    }

    printVector(&vector);

    vector.emplace(&vector, 11, vector.size / 2);
    printVector(&vector);

    vector.emplace(&vector, 11, 0);
    printVector(&vector);

    vector.emplace(&vector, 11, vector.size - 1);
    printVector(&vector);

    vector.erase(&vector, vector.size / 3);
    printVector(&vector);

    vector.erase(&vector, vector.size - 1);
    printVector(&vector);

    vector.erase(&vector, 0);
    printVector(&vector);

    printf("%d\n", vector.operations.i);

    vector.clear(&vector);

    return 0;
}