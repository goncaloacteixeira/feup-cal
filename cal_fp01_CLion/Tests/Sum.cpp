/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{
    int sum[size + 1][size];
    string min[size + 1];

    min[0] = "-";

    // encher a primeira linha com zeros
    // uma vez que 1 <= m <= n
    for (int i = 0; i < size; i++) {
        sum[0][i] = 100000;
    }


    for (int m = 1; m <= size; m++) {
        int aux = 100000;
        for (int i = 0; i < size; i++) {
            sum[m][i] = sequence[i];

            if (i + m - 1 >= size) {
                sum[m][i] = 100000;
            } else {
                for (int j = i + 1; j - i + 1 <= m && j < size; j++) {
                    sum[m][i] += sequence[j];
                }
            }

            if (sum[m][i] < aux) {
                min[m] = to_string(sum[m][i]) + "," + to_string(i) + ";";
                aux = sum[m][i];
            }
        }
    }

    string res = "";
    for (int i = 1; i < size + 1; i++) {
        res += min[i];
    }


	return res;
}

