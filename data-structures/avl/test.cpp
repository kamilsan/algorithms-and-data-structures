#include <iostream>

#include "avl.hpp"

int main()
{
  AVL<int> avl;
  int valuesToInsert[] = { 12, 7, 40, 4, 8, 9, 3, 6, 2, 30, 42, 35, 41, 45 };
  for(int value : valuesToInsert)
    avl.insert(value);

  std::cout << "Size: " << avl.size() << std::endl;
  std::cout << "Is empty? " << std::boolalpha << avl.isEmpty() << std::endl;
  std::cout << "Contains 4: " << std::boolalpha << avl.contains(4) << std::endl;
  std::cout << "Contains 10: " << std::boolalpha << avl.contains(10) << std::endl;

  std::cout << "In order:" << std::endl;
  avl.traverse([](const int& val) { std::cout << val << " "; }, 
    AVL<int>::TraversalOrder::InOrder);
  std::cout << std::endl;

  std::cout << "Preorder:" << std::endl;
  avl.traverse([](const int& val) { std::cout << val << " "; }, 
    AVL<int>::TraversalOrder::PreOrder);
  std::cout << std::endl;

  std::cout << "Postorder:" << std::endl;
  avl.traverse([](const int& val) { std::cout << val << " "; }, 
    AVL<int>::TraversalOrder::PostOrder);
  std::cout << std::endl;

  std::cout << "Level order:" << std::endl;
  avl.traverse([](const int& val) { std::cout << val << " "; }, 
    AVL<int>::TraversalOrder::LevelOrder);
  std::cout << std::endl << std::endl;
  
  int valuesToRemove[] = { 3, 2, 7, 40, 4, 6, 8, 9, 12, 30, 35, 41, 42, 45 };

  for(int value : valuesToRemove)
  {
    std::cout << "Remove " << value << "..." << std::endl;
    avl.remove(value);
    avl.traverse([](const int& val) { std::cout << val << " "; });
    std::cout << std::endl;
  }

  return 0;
}