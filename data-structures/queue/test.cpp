#include <iostream>

#include "queue.hpp"

int main()
{
  Queue<int> queue;
  std::cout << "Enqueuing values: 4, 6, 2, 3, 1" << std::endl;
  queue.enqueue(4);
  queue.enqueue(6);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(1);

  std::cout << "Front: " << queue.front() << std::endl;
  std::cout << "Back: " << queue.back() << std::endl;
  std::cout << "Size: " << queue.size() << std::endl;
  std::cout << "Empty: " << std::boolalpha << queue.isEmpty() << std::endl;

  while(!queue.isEmpty())
  {
    std::cout << "Dequeuing: " << queue.dequeue() << std::endl;
  }

  std::cout << "Empty: " << std::boolalpha << queue.isEmpty() << std::endl;
  std::cout << "Enqueuing values:  7, 3, 11, 3" << std::endl;
  queue.enqueue(7);
  queue.enqueue(3);
  queue.enqueue(11);
  queue.enqueue(3);
  
  std::cout << "Dequeuing: " << queue.dequeue() << std::endl;
  std::cout << "Dequeuing: " << queue.dequeue() << std::endl;

  std::cout << "Enqueuing: 42, 1" << std::endl;
  queue.enqueue(42);
  queue.enqueue(1);

  while(!queue.isEmpty())
  {
    std::cout << "Dequeuing: " << queue.dequeue() << std::endl;
  }

  return 0;
}