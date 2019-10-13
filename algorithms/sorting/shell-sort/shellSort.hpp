#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void shellSort(std::vector<T>& data)
{
  // Gap sequence experimentally found by Marcin Ciura (OEIS A102549)
  size_t gaps[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
  for(size_t gap : gaps)
  {
    for(size_t i = gap; i < data.size(); ++i)
    {
      auto value = data[i];
      size_t j = i;
      while(j >= gap && compare()(value, data[j-gap]))
      {
        data[j] = data[j-gap];
        j -= gap;
      }
      data[j] = value;
    }
  }
}
