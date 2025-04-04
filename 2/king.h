#ifndef KING_H
#define KING_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

bool ReadInput(const std::string& input_filename, int& n, std::vector<std::vector<int>>& board);

void ComputePath(int n, const std::vector<std::vector<int>>& board,
                 std::vector<std::vector<int>>& dp, std::vector<std::vector<char>>& path);

std::string ReconstructRoute(int n, const std::vector<std::vector<char>>& path);

void WriteOutput(const std::string& output_filename, int min_sum, const std::string& route);

#endif