#ifndef ARTIFACT_SOLVER_H
#define ARTIFACT_SOLVER_H

#include <vector>
#include <fstream>
// FIX ME Неиспользованный импорт
//#include <string>
#include <iostream>

bool ReadInput(std::ifstream& stream, int& n, int& b, std::vector<int>& weights, std::vector<int>& volumes);

bool ValidateInput(int n, int b, const std::vector<int>& weights, const std::vector<int>& volumes);

void FillDPTables(int n, int b, const std::vector<int>& weights, const std::vector<int>& volumes,
                  std::vector<std::vector<int>>& main_vector, std::vector<std::vector<int>>& count,
                  std::vector<std::vector<int>>& volume_main);

void FindBestSolution(int n, int b, const std::vector<std::vector<int>>& main_vector,
                      const std::vector<std::vector<int>>& count,
                      const std::vector<std::vector<int>>& volume_main,
                      int& best_weight, int& best_count, int& best_volume, int& best_j);

void OutputResults(int best_weight, int best_volume, int n, int best_j,
                   const std::vector<std::vector<int>>& main_vector,
                   const std::vector<int>& weights);

void FindNumbers(const std::vector<std::vector<int>>& main_vector, const std::vector<int>& weights, int i, int j);

#endif