#include "declarations.hpp"

#include <algorithm>

std::vector<int> lis(const std::vector<int>& nums)
{
  int n = nums.size();
  if(n == 0) return {};
  int* dp = new int[n];
  dp[0] = 1;
  int solutionLen = 1;
  int globalMaxIdx = 0;
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
    if(localMax > solutionLen)
    {
      solutionLen = localMax;
      globalMaxIdx = i;
    }
  }
  
  std::vector<int> solution;
  solution.reserve(solutionLen);
  solution.push_back(nums[globalMaxIdx]);
  solutionLen--;
  while(solutionLen > 0)
  {
    for(int i = globalMaxIdx - 1; i >= 0; --i)
    {
      if(dp[i] == solutionLen && nums[i] < nums[globalMaxIdx])
      {
        solution.push_back(nums[i]);
        solutionLen--;
        globalMaxIdx = i;
      }
    }
  }
  delete[] dp;
  
  std::reverse(solution.begin(), solution.end());
  return solution;
}