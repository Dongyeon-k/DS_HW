#include <iostream>
#include <utility>
#include <vector>

#include "functions.hpp"

int main()
{
    int n = 6;
    std::vector<std::pair<int, int>> comparisons = {{1, 5}, {3, 4}, {5, 4}, {4, 2}, {4, 6}, {5, 2}};
    std::cout << countKnownRankStudents(n, comparisons) << std::endl; // 1
    return 0;
}
