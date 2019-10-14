#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void quickSort(std::vector<T>& data)
{
  auto partition = [&](size_t l, size_t r) -> size_t
  {
    size_t mid = l + (r-l)/2;
    auto pivot = data[mid];
    size_t i = l;
    size_t j = r;
    while(true)
    {
      while(compare()(pivot, data[j]))
        j--;
      while(compare()(data[i], pivot))
        i++;
      if(i < j)
      {
        std::swap(data[i], data[j]);
        i++;
        j--;
      }
      else return j;
    }
  };
  std::function<void(size_t, size_t)> sort;
  sort = [&](size_t l, size_t r)
  {
    if(l < r)
    {
      size_t pivot = partition(l, r);
      sort(l, pivot);
      sort(pivot+1, r);
    }
  };

  sort(0, data.size() - 1);
}