#include "functions.hpp"

#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

void flightRoutes(int n, std::vector<std::vector<int>> &routes)
{
    const long long INF = numeric_limits<long long>::max() / 4;
    const long long MOD = 1000000007;

    vector<vector<pair<int, long long>>> graph(n + 1);

    for (const auto &route : routes)
    {
        int from = route[0];
        int to = route[1];
        long long cost = route[2];
        graph[from].push_back({to, cost});
    }

    vector<long long> dist(n + 1, INF);
    vector<long long> path_count(n + 1, 0);
    vector<int> min_flights(n + 1, numeric_limits<int>::max());
    vector<int> max_flights(n + 1, numeric_limits<int>::min());

    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1] = 0;
    path_count[1] = 1;
    min_flights[1] = 0;
    max_flights[1] = 0;

    pq.push({0, 1}); // {cost, dest}

    while (!pq.empty())
    {
        auto [current_dist, city] = pq.top();
        pq.pop();

        if (current_dist != dist[city])
            continue;

        for (const auto &[next_city, cost] : graph[city])
        {
            long long next_dist = current_dist + cost;
            if (next_dist < dist[next_city])
            {
                dist[next_city] = next_dist;
                path_count[next_city] = path_count[city];
                min_flights[next_city] = min_flights[city] + 1;
                max_flights[next_city] = max_flights[city] + 1;
                pq.push({next_dist, next_city});
            }
            else if (next_dist == dist[next_city])
            {
                path_count[next_city] = (path_count[next_city] + path_count[city]) % MOD;
                min_flights[next_city] = min(min_flights[next_city], min_flights[city] + 1);
                max_flights[next_city] = max(max_flights[next_city], max_flights[city] + 1);
            }
        }
    }

    cout << dist[n] % MOD << ' ' << path_count[n] % MOD << ' ' << min_flights[n] << ' ' << max_flights[n] << std::endl;
}
