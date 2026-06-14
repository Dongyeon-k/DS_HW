#include <vector>

#include "functions.hpp"

int main()
{
    std::vector<std::vector<int>> routes;
    routes.push_back(std::vector<int>({1, 4, 5}));
    routes.push_back(std::vector<int>({1, 2, 4}));
    routes.push_back(std::vector<int>({2, 4, 5}));
    routes.push_back(std::vector<int>({1, 3, 2}));
    routes.push_back(std::vector<int>({3, 4, 3}));
    flightRoutes(4, routes); // 5 2 1 2
    return 0;
}