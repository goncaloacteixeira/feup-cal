#include <iostream>
#include <chrono>
#include <cstring>


double recursiveFibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
}


double dpFibonacci(int n) {
    double arr[n + 1];
    arr[0] = 0;
    arr[1] = 1;

    for (int i = 2; i <= n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n];
}


void printUsage(char* f) {
    std::cout << "Usage: " << std::endl;
    std::cout << "   " << f << " <number> <rec | dp>\n\n";
}


int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);

    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    if (std::strcmp("rec", argv[2]) == 0) {
        auto start = std::chrono::high_resolution_clock::now();
        double r = recursiveFibonacci(n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Result: " << r << std::endl;

        std::cout << "Recursive method took: " << duration.count() << " microseconds." << std::endl;
    }

    if (std::strcmp("dp", argv[2]) == 0) {
        auto start = std::chrono::high_resolution_clock::now();
        double r = dpFibonacci(n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Result: " << r << std::endl;

        std::cout << "DynamicP method took: " << duration.count() << " microseconds." << std::endl;
    }

    return 0;
}
