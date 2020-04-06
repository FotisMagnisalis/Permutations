#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>


int permutationLen, circlesCount, permutationIndex, totalTranspositions;
std::string permutationInput;

void PrintPermutation(int* inverse);

void PrintCircles(int circlesIndex, std::vector<int>* circles);

std::vector<int>* FindCircles(int permutation[]);

std::vector<int>* FindTranspositions(std::vector<int>* circles);