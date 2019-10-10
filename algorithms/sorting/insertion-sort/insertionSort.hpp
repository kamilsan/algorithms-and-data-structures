#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void insertionSort(std::vector<T>& data)
{
  for(size_t i = 1; i < data.size(); ++i)
  {
    auto value = data[i];
    long j = i - 1;
    while(j >= 0 && compare()(value, data[j]))
    {
      data[j+1] = data[j];
      j--;
    }
    data[j+1] = value;
  }
}