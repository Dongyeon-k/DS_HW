#include "functions.hpp"

#include <cstdlib>
#include <limits>
#include <vector>

namespace {

int manhattan(const std::vector<int>& a, const std::vector<int>& b) {
    return std::abs(a[0] - b[0]) + std::abs(a[1] - b[1]);
}

}  // namespace

int minDistance(std::vector<std::vector<int>>& points) {
    const int n = static_cast<int>(points.size());
    if (n == 0) {
        return 0;
    }

    std::vector<bool> used(n, false);
    std::vector<int> best(n, std::numeric_limits<int>::max());
    best[0] = 0;

    int answer = 0;
    for (int step = 0; step < n; ++step) {
        int cur = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && (cur == -1 || best[i] < best[cur])) {
                cur = i;
            }
        }

        used[cur] = true;
        answer += best[cur];

        for (int next = 0; next < n; ++next) {
            if (!used[next]) {
                const int dist = manhattan(points[cur], points[next]);
                if (dist < best[next]) {
                    best[next] = dist;
                }
            }
        }
    }

    return answer;
}
