#ifndef GA_H
#define GA_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;
using VectDouble = std::vector<double>;
using BoardDouble = std::vector<std::vector<double>>;

double runAi(VectDouble genome);

// In GA.h
BoardDouble initializePopulationFromGenome(const VectDouble &genome, int populationSize, double mutationRate = 0.01);

double fitnessFunction(const VectDouble &genome, const int &numTrials);

VectDouble evaluatePopulation(const BoardDouble &population, int numTrials = 5);
#endif