#include "declarations.hpp"

int lis(const std::vector<int>& nums)
{
  int n = nums.size();
  if(n == 0) return 0;
  int* dp = new int[n];
  dp[0] = 1;
  int solution = 1;
  for(int i = 1; i < n; ++i)
  {
    int localMax = 1;
    for(int j = 0; j < i; ++j)
    {
      if(nums[i] > nums[j])
      {
        localMax = std::max(localMax, 1 + dp[j]);
      }
    }
    dp[i] = localMax;
    if(localMax > solution) solution = localMax;
  }
  
  delete[] dp;
  
  return solution;
}