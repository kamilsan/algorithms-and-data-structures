#include <iostream>

#include "declarations.hpp"

int main()
{
  std::string word1 = "palingenesia";
  std::string word2 = "ungenerous";
  auto edits = editDistance(word1, word2);
  std::cout << "Edit distance between " << "\"" << word1 << "\"" << 
    " and " << "\"" << word2 << "\"" << " is equal to " << edits.size() << std::endl;

  for(auto edit : edits)
  {
    if(edit.type == EditOperationType::Add)
      std::cout << "+" << edit.destination << std::endl;
    else if(edit.type == EditOperationType::Remove)
      std::cout << "-" << edit.source << std::endl;
    else // Replace
      std::cout << edit.source << "->" << edit.destination << std::endl;
  }

  return 0;
}