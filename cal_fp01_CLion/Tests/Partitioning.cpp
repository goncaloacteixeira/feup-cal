/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <climits>


int s_recursive(int n, int k) {
    if (1 < k && k < n) {
        return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
    }
    return 1;
}

int s_dynamic(int n,int k) {
    int s[n+1][k+1];

    // fill with "infinity" has we dont need the n = 0 values
    for (int i = 0; i <= k; i++) {
        s[0][i] = INT_MAX;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < k+1; j++) {
            if (1 < j && j < i) {
                s[i][j] = s[i-1][j-1] + j*s[i-1][j];
            }
            else {
                s[i][j] = 1;
            }
        }
    }

    return s[n][k];
}


int b_recursive(int n) {
    int res = 0;
    for (int k = 1; k <= n; k++) {
        res += s_recursive(n, k);
    }
    return res;
}

int b_dynamic(int n) {
    int res = 0;
    for (int k = 1; k <= n; k++) {
        res += s_dynamic(n, k);
    }
    return res;
}


