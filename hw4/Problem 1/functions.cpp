#include "functions.hpp"

#include <climits>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int coinCombinations(int target, std::vector<int> &coins)
{
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    int MOD = 1000000007;

    for (int sum = 1; sum <= target; sum++)
    {
        long long ways = 0;
        for (int coin : coins)
        {
            if (sum >= coin)
            {
                ways += dp[sum - coin];
                if (ways >= MOD)
                {
                    ways %= MOD;
                }
            }
        }
        dp[sum] = ways % MOD;
    }

    return dp[target];
}
