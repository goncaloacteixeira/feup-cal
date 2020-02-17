/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {
    if (n == 1 || n == 0) {
        return n;
    }
    return factorialRecurs(n-1)*n;
}

int factorialDinam(int n) {
    int fact = 1;

    while (n != 0) {
        fact *= n;
        n--;
    }
    return fact;
}
