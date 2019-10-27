cmake_minimum_required(VERSION 2.4)
project(AlgorithmsDataStructures)

add_executable(lis
  declarations.hpp
  lis.cpp lis_test.cpp)

add_executable(lps
  declarations.hpp
  lps.cpp lps_test.cpp)

add_executable(lcs
  declarations.hpp
  lcs.cpp lcs_test.cpp)

add_executable(edit-distance
  declarations.hpp
  editDistance.cpp editDistance_test.cpp)