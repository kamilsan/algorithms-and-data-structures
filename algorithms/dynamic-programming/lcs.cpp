#include "declarations.hpp"

#include <iostream>

std::string lcs(const std::string& s1, const std::string& s2)
{
  int n1 = s1.size();
  int n2 = s2.size();
  int* dp = new int[(n1+1)*(n2+1)];
  auto map = [=](int i, int j) {return j*(n1+1) + i; };

  for(int i = 0; i <= n1; ++i)
  {
    dp[map(i, n2)] = 0;
  }
  for(int j = 0; j <= n2; ++j)
  {
    dp[map(n1, j)] = 0;
  }

  for(int i = n1 - 1; i >= 0; --i)
  {
    for(int j = n2 - 1; j >= 0; --j)
    {
      if(s1[i] == s2[j])
        dp[map(i, j)] = 1 + dp[map(i + 1, j + 1)];
      else
        dp[map(i, j)] = std::max(dp[map(i + 1, j)], dp[map(i, j + 1)]);
    }
  }

  std::string result;

  int i = 0, j = 0;
  while(i < n1 && j < n2)
  {
    if(s1[i] == s2[j])
    {
      result.push_back(s1[i]);
      i += 1;
      j += 1;
    }
    else if(dp[map(i + 1, j)] > dp[map(i, j+1)])
      i += 1;
    else
      j += 1;
  }

  delete[] dp;

  return result;
}