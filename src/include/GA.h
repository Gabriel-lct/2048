#ifndef GA_H
#define GA_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>
#include <omp.h> //for parallelisation

using Vect = std::vector<int>;
using Board = std::vector<std::vector<int>>;
using BoardVect = std::vector<Board>;
using VectDouble = std::vector<double>;
using GenomePair = std::pair<VectDouble, VectDouble>;
using BoardDouble = std::vector<std::vector<double>>;

double runAi(const VectDouble &genome);

void runGeneticAlgorithm(BoardDouble &population, int &maxGamesPerGenome, int maxGenerations, double mutationRate, double mutationStrength);

// In GA.h
BoardDouble initializePopulationFromGenome(const VectDouble &firstGenome, int populationSize, double mutationRate = 0.01);

double fitnessFunction(const VectDouble &genome, const int &numTrials, const int &genomeIndex);

VectDouble evaluatePopulation(const BoardDouble &population, int numTrials);

BoardDouble rouletteWheelSelection(const BoardDouble &population, VectDouble &fitnessScores, int numSelection);

GenomePair singlePointCrossover(const VectDouble &parent1, const VectDouble &parent2);

BoardDouble createNextGeneration(const BoardDouble &selectedGenomes, int populationSize);

void mutateGenome(VectDouble &genome, double mutationRate, double mutationStrength);

void mutatePopulation(BoardDouble &population, double mutationRate, double mutationStrength);
#endif