#include "functions.hpp"

#include <vector>

int coinCombinations(int target, std::vector<int>& coins) {
    const int MOD = 1000000007;

    std::vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int sum = 1; sum <= target; ++sum) {
        long long ways = 0;
        for (int coin : coins) {
            if (sum >= coin) {
                ways += dp[sum - coin];
                if (ways >= MOD) {
                    ways %= MOD;
                }
            }
        }
        dp[sum] = static_cast<int>(ways % MOD);
    }

    return dp[target];
}
