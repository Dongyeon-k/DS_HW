#include <iostream>
#include <vector>

#include "functions.hpp"

int main() {
    std::vector<std::vector<int>> points;

    points.push_back(std::vector<int>({3, 12}));
    points.push_back(std::vector<int>({-2, 5}));
    points.push_back(std::vector<int>({-4, 1}));
    points.push_back(std::vector<int>({-5, 8}));
    points.push_back(std::vector<int>({6, 18}));
    points.push_back(std::vector<int>({5, 10}));
    points.push_back(std::vector<int>({7, 8}));

    std::cout << minDistance(points) << std::endl;  // 41
    return 0;
}
