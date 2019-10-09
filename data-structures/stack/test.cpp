#include <iostream>

#include "stack.hpp"

int main()
{
  Stack<int> stack;
  std::cout << "Pushing values: 2, 1, 4, 7" << std::endl;
  stack.push(2);
  stack.push(1);
  stack.push(4);
  stack.push(7);

  std::cout << "Peek: " << stack.peek() << std::endl;
  std::cout << "Stack empty: " << std::boolalpha << stack.isEmpty() << std::endl;
  std::cout << "Stack size: " << stack.size() << std::endl;

  while(!stack.isEmpty())
  {
    std::cout << "Popped: " << stack.pop() << std::endl;
  }

  std::cout << "Pushing 5, 6, 7" << std::endl;
  stack.push(5);
  stack.push(6);
  stack.push(7);

  std::cout << "Popped: " << stack.pop() << std::endl;
  std::cout << "Popped: " << stack.pop() << std::endl;
  std::cout << "Peek: " << stack.peek() << std::endl;

  std::cout << "Pushing 1, 2, 3" << std::endl;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  while(!stack.isEmpty())
  {
    std::cout << "Popped: " << stack.pop() << std::endl;
  }

  return 0;
}