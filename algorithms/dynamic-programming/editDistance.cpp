#include "declarations.hpp"

std::vector<EditOperation> editDistance(const std::string& s1, const std::string& s2)
{
  int n1 = s1.size();
  int n2 = s2.size();
  int* dp = new int[(n1+1)*(n2+1)];
  auto map = [&](int i, int j) -> int {return j*(n1+1) + i;};
  
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
  
  int editDistance = dp[0];
  std::vector<EditOperation> edits;
  edits.reserve(editDistance);

  int i = 0, j = 0;
  while(i < n1 && j < n2)
  {
    if(s1[i] == s2[j])
    {
      i += 1;
      j += 1;
    }
    else
    {
      int removalDistance = dp[map(i+1, j)];
      int insertionDistance = dp[map(i, j+1)];
      int replacementDistance = dp[map(i+1, j+1)];

      int minDistance = removalDistance;

      if(insertionDistance < minDistance)
        minDistance = insertionDistance;
      if(replacementDistance < minDistance)
        minDistance = replacementDistance;

      if(minDistance == replacementDistance)
      {
        edits.push_back({EditOperationType::Replace, s1[i], s2[j]});
        i += 1;
        j += 1;
      }
      else if(minDistance == insertionDistance)
      {
        edits.push_back({EditOperationType::Add, ' ', s2[j]});
        j += 1;
      }
      else
      {
        edits.push_back({EditOperationType::Remove, s1[i], ' '});
        i += 1;
      }
    }
  }

  while(i < n1)
  {
    edits.push_back({EditOperationType::Remove, s1[i], ' '});
    i += 1;
  }

  while(j < n2)
  {
    edits.push_back({EditOperationType::Add, ' ', s2[j]});
    j += 1;
  }

  delete[] dp;
  
  return edits;
}