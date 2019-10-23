#include "declarations.hpp"

std::string lps(const std::string& str)
{
  int n = str.size();
  int* dp = new int[n*n];
  
  auto map = [&](int i, int j) -> int { return j*n+i; };
  
  for(int i = 0; i < n; ++i)
  {
    dp[map(i, i)] = 1;
  }
  for(int i = 0; i < n - 1; ++i)
  {
    dp[map(i+1, i)] = 0;
  }
  
  for(int a = 1; a < n; ++a)
  {
    for(int i = 0; i < n - a; ++i)
    {
      int j = a + i;
      if(str[i] == str[j])
      {
        dp[map(i, j)] = 2 + dp[map(i+1, j-1)];
      }
      else
      {
        dp[map(i, j)] = std::max(dp[map(i, j-1)], dp[map(i+1, j)]);
      }
    }
  }
  
  int solutionLen = dp[map(0, n-1)];
  std::string solution(solutionLen, ' ');
  solution.reserve(solutionLen);
  int i = 0;
  int j = n - 1;
  int head = 0;

  while(i < j)
  {
    if(str[i] == str[j])
    {
      solution[head] = str[i];
      solution[solutionLen - head - 1] = str[i];
      i += 1;
      j -= 1;
      head += 1;
    }
    else if(dp[map(i, j-1)] > dp[map(i+1, j)])
      j -= 1;
    else
      i += 1;
  }
  delete[] dp;
  if(i == j) 
    solution[head] = str[i];
  
  return solution;
}