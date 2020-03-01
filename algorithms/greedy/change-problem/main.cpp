#include <iostream>
#include <string>

/**
 * Greedy Algorithm for the change problem
 * @param m         amount to return
 * @param coins     array with coin stock
 * @param size      size of the array
 * @return          string with the change combination
 */
std::string change(int m, int* coins, int size) {
    std::string res;

    for (int i = size-1; i >= 0 && m > 0; i--) {
        if (coins[i] <= m) {
            res += std::to_string(coins[i]) + ";";
            m -= coins[i];
        }
    }
    if (m > 0) {
        return "cannot return change\n";
    }
    return res;
}

/**
 * Bad algorithm to the coin change problem, takes a set of coin
 * denominations (unlimited coins) and returns a string with te
 * possible best option for change.
 *
 * The purpose of this function is to help with testing if a given
 * model is canonical or not.
 *
 * @param m         amount to return
 * @param coins     set of denominations
 * @param size      size of the array
 * @return          string with change combinations
 */
std::string change2(int m, int* coins, int size) {
    std::string res;
    while (m != 0) {
        for (int i = size - 1; i >= 0 && m > 0; i--) {
            if (coins[i] <= m) {
                res += std::to_string(coins[i]) + ";";
                m -= coins[i];
            }
        }
    }
    return res;
}

/**
 * Function to test if a given set is canonical or not.
 *
 * if a solution for any 'm' in the given interval:
 *      coins[2] + 1 < m < coins[size-2] + coins[size-2]
 * is not the optimal global solution then the system is not
 * canonical therefor it cannot be used in a greedy algorithm
 * as we cannot determine whether the best local solution will
 * be the optimal global solution to a given problem.
 *
 * In that latter case we should try another aproach:
 *      Dynamic Programming
 *
 * @param size          size of the array
 * @param coins         array of the denominations
 * @return
 */
bool test_opt(int size, int* coins) {
    for (int m = coins[2] + 2; m < coins[size-1] + coins[size-2]; m++) {
        std::cout << "Change for " << m << ": ";
        std::cout << change2(m, coins, size) << std::endl;
    }
    std::cout << "Are all the solutions optimal (y/n): ";
    std::string answer;
    std::getline(std::cin, answer);
    return answer == "y" || answer == "Y";
}


int main() {
    int coins1[] = {1,1,1,4,4,5}; // not a canonical example
    test_opt(6, coins1);     // this test will prove that

    int coins2[] = {1,1,2,2,2,5,5};                  // this is a canonical example (such is the EURO)
    std::cout << change(9, coins2, 7);      // The output will be the global best
                                                     // output: 5;2;2;

    return 0;
}
