#include "functions.hpp"

#include <utility>
#include <vector>

int countKnownRankStudents(int n,
                           std::vector<std::pair<int, int>> &comparisons)
{
    std::vector<std::vector<bool>> reachable(n + 1,
                                             std::vector<bool>(n + 1, false));

    for (const auto &[shorter, taller] : comparisons)
    {
        reachable[shorter][taller] = true;
    }

    for (int mid = 1; mid <= n; ++mid)
    {
        for (int from = 1; from <= n; ++from)
        {
            if (!reachable[from][mid])
            {
                continue;
            }
            for (int to = 1; to <= n; ++to)
            {
                reachable[from][to] = reachable[from][to] || reachable[mid][to];
            }
        }
    }

    int known_count = 0;
    for (int student = 1; student <= n; ++student)
    {
        int comparable = 0;
        for (int other = 1; other <= n; ++other)
        {
            if (student == other)
            {
                continue;
            }
            if (reachable[student][other] || reachable[other][student])
            {
                ++comparable;
            }
        }
        if (comparable == n - 1)
        {
            ++known_count;
        }
    }

    return known_count;
}
