/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <fstream>

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


int graph() {
    int n = 10;

    int *arr;
    ofstream myCSV;
    myCSV.open("../results.csv");

    if (!myCSV.is_open()) {
        return 1;
    }

    myCSV << "n,time(ms)" << endl;

    while (n < 500) {
        double time = 0;
        for (int i = 1; i <= 1000; i++) {
            arr = (int*) malloc (n*sizeof(int));
            for (int j = 0; j < n; j++) {
                arr[j] = rand() % 10*n;
            }
            auto start = chrono::high_resolution_clock::now();
            calcSum(arr, n);
            auto end = chrono::high_resolution_clock::now();
            free(arr);
            time += chrono::duration_cast<chrono::milliseconds>(end-start).count();
        }

        myCSV << n << "," << time/1000.0 << endl;
        n += 10;
    }
    return 0;
}




