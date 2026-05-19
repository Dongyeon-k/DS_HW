#include "functions.hpp"

#include <limits>
#include <vector>

int minDistance(std::vector<std::vector<int>>& points) {
    const int n = points.size();
    if (n == 0) {
        return 0;
    }

    std::vector<bool> visited(n, false);
    std::vector<int> distance(n, std::numeric_limits<int>::max());
    distance[0] = 0;

    int total_distance = 0;

    for (int count = 0; count < n; ++count) {
        int current = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] &&
                (current == -1 || distance[i] < distance[current])) {
                current = i;
            }
        }

        visited[current] = true;
        total_distance += distance[current];

        for (int next = 0; next < n; ++next) {
            if (visited[next]) {
                continue;
            }

            int x_distance = points[current][0] - points[next][0];
            if (x_distance < 0) {
                x_distance = -x_distance;
            }

            int y_distance = points[current][1] - points[next][1];
            if (y_distance < 0) {
                y_distance = -y_distance;
            }

            const int new_distance = x_distance + y_distance;
            if (new_distance < distance[next]) {
                distance[next] = new_distance;
            }
        }
    }

    return total_distance;
}
