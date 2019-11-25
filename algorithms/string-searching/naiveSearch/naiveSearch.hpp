#pragma once

#include <vector>
#include <string>
#include <cstddef>

std::vector<size_t> naiveSearch(std::string str, std::string pattern)
{
  size_t n = str.size();
  size_t p = pattern.size();
  
  std::vector<size_t> offsets;

  for(size_t i = 0; i <= n - p; ++i)
  {
    bool match = true;
    for(size_t j = 0; j < p; ++j)
    {
      if(str[i+j] != pattern[j])
      {
        match = false;
        break;
      }
    }

    if(match)
    {
      offsets.push_back(i);
    }
  }

  return offsets;
}