#pragma once

#include <vector>
#include <string>
#include <cstddef>

std::vector<size_t> naiveSearch(std::string str, std::string pattern)
{
  size_t n = str.size();
  size_t m = pattern.size();
  
  std::vector<size_t> offsets;

  if(m == 0)
  {
    for(size_t i = 0; i < n; ++i) 
      offsets.push_back(i);
    return offsets;
  }

  for(size_t i = 0; i <= n - m; ++i)
  {
    size_t j = 0;
    for(; j < m; ++j)
    {
      if(str[i+j] != pattern[j])
        break;
    }

    if(j == m)
      offsets.push_back(i);
  }

  return offsets;
}