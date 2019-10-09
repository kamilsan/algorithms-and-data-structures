#include <iostream>

#include "doublyLinkedList.hpp"

int main()
{
  DoublyLinkedList<int> list;
  list.add_front(12);
  list.add_front(42);
  list.add_front(53);

  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Front: " << list.get_front() << std::endl;
  std::cout << "Size: " << list.size() << std::endl;

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

  std::cout << "Removing 4..." << std::endl;
  list.remove(4);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Removing 1..." << std::endl;
  list.remove(1);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  std::cout << "Adding some elements to the back..." << std::endl;
  list.add_back(5);
  list.add_back(7);
  list.add_back(-2);

  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl << "Back: " << list.get_back() << std::endl;

  std::cout << "Removing 7..." << std::endl;
  list.remove(7);
  list.for_each([](const int& n) { std::cout << n << " ";});
  std::cout << std::endl;

  return 0;
}