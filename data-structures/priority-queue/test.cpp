#include <iostream>
#include <string>
#include <vector>

#include "priorityQueue.hpp"

struct Person
{
  std::string name;
  unsigned rang;

  Person(): name("Noname"), rang(1000) {}
  Person(std::string name_, unsigned rang_): name(name_), rang(rang_) {}

  friend std::ostream& operator<<(std::ostream& os, const Person& p)
  {
    os << p.name << " (rang: " << p.rang << ")";
    return os;
  }
};

struct PersonComparator
{
  bool operator()(const Person& p1, const Person& p2)
  {
    return p1.rang < p2.rang;
  }
};

int main()
{
  PriorityQueue<Person, PersonComparator> queue;

  std::cout << "Queue size: " << queue.size() << " is empty: " 
    << std::boolalpha << queue.isEmpty() << std::endl;

  std::vector<Person> people = {{"John", 5}, {"Sir Arthur", 1}, {"Alice", 2}};

  for(auto person : people)
  {
    std::cout << person << " appeared!" << std::endl;
    queue.enqueue(person);
  }
  std::cout << "Queue size: " << queue.size() << " is empty: " 
    << std::boolalpha << queue.isEmpty() << std::endl;

  std::cout << "Peek: " << queue.peek() << std::endl;

  std::cout << "King Sejong (rang: 0) appeared!" << std::endl;
  queue.enqueue({"King Sejong", 0});
  std::cout << "Peek: " << queue.peek() << std::endl;

  std::cout << "Leaving queue in the following order:" << std::endl;
  while(!queue.isEmpty())
  {
    std::cout << queue.dequeue() << std::endl;
  }

  return 0;
}