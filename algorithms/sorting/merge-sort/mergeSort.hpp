#pragma once

#include <functional>

template <typename T, typename compare = std::less<T>>
void mergeSort(std::vector<T>& data)
{
  auto merge = [&](std::vector<T>& arr, unsigned l, unsigned m, unsigned r)
  {
    unsigned n1 = m-l+1;
    unsigned n2 = r-m;
    std::vector<T> L;
    L.reserve(n1);
    std::vector<T> R;
    R.reserve(n2);
    for(unsigned i = 0; i < n1; ++i)
      L.push_back(arr[l+i]);
    for(unsigned i = 0; i < n2; ++i)
      R.push_back(arr[m+1+i]);

    unsigned i = 0, j = 0, k = l;
    while(i < n1 && j < n2)
    {
      if(compare()(L[i], R[j]))
      {
        arr[k] = L[i];
        i += 1;
      }
      else
      {
        arr[k] = R[j];
        j += 1;
      }
      k += 1;
    }

    while(i < n1)
    {
      arr[k] = L[i];
      i += 1;
      k += 1;
    }
    while(j < n2)
    {
      arr[k] = R[j];
      j += 1;
      k += 1;
    }
  };
  std::function<void(std::vector<T>&, unsigned, unsigned)> sort;
  sort = [&](std::vector<T>& arr, unsigned l, unsigned r)
  {
    if(l < r)
    {
      unsigned m = l + (r-l)/2;
      sort(arr, l, m);
      sort(arr, m+1, r);
      merge(arr, l, m, r);
    }
  };
  sort(data, 0, data.size() - 1);
}
