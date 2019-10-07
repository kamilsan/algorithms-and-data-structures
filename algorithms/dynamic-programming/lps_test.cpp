#include <iostream>

#include "declarations.hpp"

int main()
{
  std::string testString = "no lemon, no melon!";
  int lpsLen = lps(testString);
  std::cout << "Longest palindromic subsequance in string " 
    << testString << " has length of " << lpsLen << std::endl;

  return 0;
}