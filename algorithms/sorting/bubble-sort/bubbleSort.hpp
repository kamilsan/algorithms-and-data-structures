#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void bubbleSort(std::vector<T>& data)
{
  for(auto it = data.begin(); it != data.end(); ++it)
  {
    for(auto it2 = it + 1; it2 != data.end(); ++it2)
    {
      if(compare()(*it2, *it))
      {
        std::swap(*it2, *it);
      }
    }
  }
}