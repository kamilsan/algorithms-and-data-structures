#pragma once

#include <vector>
#include <string>
#include <cstddef>

std::vector<size_t> kmp(std::string str, std::string pattern)
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

  size_t* shifts = new size_t[m];
  shifts[0] = 0;

  size_t prefixLen = 0;
  for(size_t i = 1; i < m; ++i)
  {
    while(prefixLen > 0 && pattern[i] != pattern[prefixLen])
      prefixLen = shifts[prefixLen-1];

    if(pattern[i] == pattern[prefixLen])
      prefixLen += 1;
    
    shifts[i] = prefixLen;
  }

  size_t matchingCharacters = 0;
  for(size_t i = 0; i < n; ++i)
  {
    while(matchingCharacters > 0 && str[i] != pattern[matchingCharacters])
      matchingCharacters = shifts[matchingCharacters-1];

    if(str[i] == pattern[matchingCharacters])
      matchingCharacters += 1;

    if(matchingCharacters == m)
    {
      offsets.push_back(i - m + 1);
      matchingCharacters = shifts[matchingCharacters-1];
    }
  }

  delete[] shifts;

  return offsets;
}