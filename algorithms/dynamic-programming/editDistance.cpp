#include "declarations.hpp"

int editDistance(const std::string& s1, const std::string& s2)
{
  if(s1.size() == 0) return s2.size();
  if(s2.size() == 0) return s1.size();
  int n1 = s1.size();
  int n2 = s2.size();
  int* dp = new int[(n1+1)*(n2+1)];
  auto map = [&](int i, int j) -> int {return j*n1 + i;};
  
  for(int i = 0; i <= n1; ++i)
  {
    dp[map(i, n2)] = n1 - i;
  }
  
  for(int j = 0; j <= n2; ++j)
  {
    dp[map(n1, j)] = n2 - j;
  }
  
  for(int i = n1 - 1; i >= 0; --i)
  {
    for(int j = n2 - 1; j >= 0; --j)
    {
      if(s1[i] == s2[j]) dp[map(i, j)] = dp[map(i+1, j+1)];
      else dp[map(i, j)] = 
        1 + std::min(dp[map(i+1, j)], std::min(dp[map(i, j+1)], dp[map(i+1, j+1)]));
    }
  }
  
  int sol = dp[0];
  delete[] dp;
  
  return sol;
}