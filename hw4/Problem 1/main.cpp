#include <iostream>
#include <vector>

#include "functions.hpp"

int main() {
    std::vector<int> coins = {1, 2, 3};
    std::cout << coinCombinations(4, coins) << std::endl;  // 7
    return 0;
}
