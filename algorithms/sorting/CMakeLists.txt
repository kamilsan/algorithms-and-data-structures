cmake_minimum_required(VERSION 2.4)
project(AlgorithmsDataStructures)

add_executable(sorting
  bubble-sort/bubbleSort.hpp
  selection-sort/selectionSort.hpp
  insertion-sort/insertionSort.hpp
  merge-sort/mergeSort.hpp
  shell-sort/shellSort.hpp
  test.cpp)