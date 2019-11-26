#include <iostream>

#include "kmp.hpp"

int main()
{
  std::string str = "ababaaabbabaadaaaccaaaaabbabaadaaaabbabaadaaaaabbabaaabbabaada";
  std::string pattern = "aaabbabaada";
  
  auto result = kmp(str, pattern);
  for(auto r : result)
  {
    std::cout << "Found pattern at offset " << r << std::endl;
  }

  return 0;
}