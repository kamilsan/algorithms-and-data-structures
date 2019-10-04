#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void selectionSort(std::vector<T>& data)
{
  for(auto it = data.begin(); it != data.end(); ++it)
  {
    T min = *it;
    auto minIt = it;
    for(auto it2 = it + 1; it2 != data.end(); ++it2)
    {
      if(*it2 < min)
      {
        min = *it2;
        minIt = it2;
      }
    }
    std::swap(*it, *minIt);
  }
}