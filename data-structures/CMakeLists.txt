cmake_minimum_required(VERSION 2.4)
project(AlgorithmsDataStructures)

add_executable(dynamic-array
  dynamic-array/dynamicArray.hpp
  dynamic-array/test.cpp)

add_executable(linked-list
  linked-list/linkedList.hpp
  linked-list/test.cpp)

add_executable(doubly-linked-list
  doubly-linked-list/doublyLinkedList.hpp
  doubly-linked-list/test.cpp)

add_executable(stack
  stack/stack.hpp
  stack/test.cpp)

add_executable(queue
  queue/queue.hpp
  queue/test.cpp)

add_executable(heap
  heap/heap.hpp
  heap/test.cpp)

add_executable(bst
  bst/bst.hpp
  bst/test.cpp)

add_executable(priorityQueue
  priority-queue/priorityQueue.hpp
  priority-queue/test.cpp)

add_executable(avl
  avl/avl.hpp
  avl/test.cpp)

add_executable(hashset
  hashset/hashset.hpp
  hashset/test.cpp)