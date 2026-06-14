#include "functions.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

void flightRoutes(int n, std::vector<std::vector<int>>& routes) {
    const long long INF = std::numeric_limits<long long>::max() / 4;
    const long long MOD = 1000000007;

    std::vector<std::vector<std::pair<int, long long>>> graph(n + 1);
    for (const auto& route : routes) {
        int from = route[0];
        int to = route[1];
        long long cost = route[2];
        graph[from].push_back({to, cost});
    }

    std::vector<long long> dist(n + 1, INF);
    std::vector<long long> path_count(n + 1, 0);
    std::vector<int> min_flights(n + 1, std::numeric_limits<int>::max());
    std::vector<int> max_flights(n + 1, std::numeric_limits<int>::min());

    using State = std::pair<long long, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    dist[1] = 0;
    path_count[1] = 1;
    min_flights[1] = 0;
    max_flights[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [current_dist, city] = pq.top();
        pq.pop();

        if (current_dist != dist[city]) {
            continue;
        }

        for (const auto& [next_city, cost] : graph[city]) {
            long long next_dist = current_dist + cost;

            if (next_dist < dist[next_city]) {
                dist[next_city] = next_dist;
                path_count[next_city] = path_count[city];
                min_flights[next_city] = min_flights[city] + 1;
                max_flights[next_city] = max_flights[city] + 1;
                pq.push({next_dist, next_city});
            } else if (next_dist == dist[next_city]) {
                path_count[next_city] =
                    (path_count[next_city] + path_count[city]) % MOD;
                min_flights[next_city] =
                    std::min(min_flights[next_city], min_flights[city] + 1);
                max_flights[next_city] =
                    std::max(max_flights[next_city], max_flights[city] + 1);
            }
        }
    }

    std::cout << dist[n] << ' ' << path_count[n] % MOD << ' '
              << min_flights[n] << ' ' << max_flights[n] << std::endl;
}
