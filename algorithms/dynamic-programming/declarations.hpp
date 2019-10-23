#pragma once

#include <vector>
#include <string>

//Longest Increasing Subsequence
std::vector<int> lis(const std::vector<int>& nums);

//Longest Palindromic Subsequence
std::string lps(const std::string& str);

//Edit distance
int editDistance(const std::string& s1, const std::string& s2);