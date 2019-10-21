#include <iostream>

#include "declarations.hpp"

int main()
{
  std::string testString = "dno lerwmon, nyo melryofn!";
  std::cout << "Longest palindromic subsequence in string " 
    << testString << " is \"" << lps(testString) << "\"" << std::endl;

  return 0;
}