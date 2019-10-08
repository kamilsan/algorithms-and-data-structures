#include <iostream>

#include "linkedList.hpp"

int main()
{
  LinkedList<int> list;
  list.add_front(12);
  list.add_front(42);
  list.add_front(53);

  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  auto f = list.get_front();
  std::cout << "Front: " << f << std::endl;

  std::cout << "Removing front..." << std::endl;
  list.remove_front();
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Adding some elements..." << std::endl;
  list.add_front(1);
  list.add_front(4);
  list.add_front(5);

  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  list.contains(4) ? std::cout << "4 is in the list." : std::cout << "4 is not on the list.";
  std::cout << std::endl;
  list.contains(35) ? std::cout << "35 is in the list." : std::cout << "35 is not on the list.";
  std::cout << std::endl;

  std::cout << "Removing 42..." << std::endl;
  list.remove(42);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Removing 5..." << std::endl;
  list.remove(5);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Removing 12..." << std::endl;
  list.remove(12);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  return 0;
}