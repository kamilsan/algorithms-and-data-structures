cmake_minimum_required(VERSION 2.4)
project(AlgorithmsDataStructures)

add_executable(naiveSearch
  naiveSearch/naiveSearch.hpp
  naiveSearch/test.cpp)

add_executable(kmp
  kmp/kmp.hpp
  kmp/test.cpp)