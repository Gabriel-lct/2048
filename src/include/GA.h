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

/**
 * @brief Runs the AI with the given genome.
 * 
 * @param genome The genome to use for the AI.
 * @return The score achieved by the AI.
 */
double runAi(const VectDouble &genome);

/**
 * @brief Displays the best genome.
 * 
 * @param genome The genome to display.
 * @param index The index of the genome.
 */
void displayBestGenome(VectDouble &genome, const int &index);

/**
 * @brief Gets the index of the best genome based on fitness scores.
 * 
 * @param fitnessScores The fitness scores of the genomes.
 * @return The index of the best genome.
 */
int getBestGenome(VectDouble &fitnessScores);

/**
 * @brief Runs the genetic algorithm to evolve the population.
 * 
 * @param population The population of genomes.
 * @param maxGamesPerGenome The maximum number of games per genome.
 * @param maxGenerations The maximum number of generations.
 * @param mutationRate The mutation rate.
 * @param mutationStrength The mutation strength.
 */
void runGeneticAlgorithm(BoardDouble &population, int &maxGamesPerGenome, int maxGenerations, double mutationRate, double mutationStrength);

/**
 * @brief Initializes the population from a given genome.
 * 
 * @param firstGenome The initial genome.
 * @param populationSize The size of the population.
 * @param mutationRate The mutation rate.
 * @return The initialized population.
 */
BoardDouble initializePopulationFromGenome(const VectDouble &firstGenome, int populationSize, double mutationRate = 0.01);

/**
 * @brief Calculates the fitness of a genome.
 * 
 * @param genome The genome to evaluate.
 * @param numTrials The number of trials to run.
 * @param genomeIndex The index of the genome.
 * @return The fitness score of the genome.
 */
double fitnessFunction(const VectDouble &genome, const int &numTrials, const int &genomeIndex);

/**
 * @brief Evaluates the fitness of the entire population.
 * 
 * @param population The population of genomes.
 * @param numTrials The number of trials to run.
 * @return A vector of fitness scores.
 */
VectDouble evaluatePopulation(const BoardDouble &population, int numTrials);

/**
 * @brief Selects genomes from the population using roulette wheel selection.
 * 
 * @param population The population of genomes.
 * @param fitnessScores The fitness scores of the genomes.
 * @param numSelection The number of genomes to select.
 * @return The selected genomes.
 */
BoardDouble rouletteWheelSelection(BoardDouble population, VectDouble fitnessScores, int numSelection);

/**
 * @brief Performs single-point crossover between two parent genomes.
 * 
 * @param parent1 The first parent genome.
 * @param parent2 The second parent genome.
 * @return A pair of child genomes.
 */
GenomePair singlePointCrossover(const VectDouble &parent1, const VectDouble &parent2);

/**
 * @brief Creates the next generation of genomes.
 * 
 * @param selectedGenomes The selected genomes from the current generation.
 * @param populationSize The size of the population.
 * @return The next generation of genomes.
 */
BoardDouble createNextGeneration(const BoardDouble &selectedGenomes, int populationSize);

/**
 * @brief Mutates a genome.
 * 
 * @param genome The genome to mutate.
 * @param mutationRate The mutation rate.
 * @param mutationStrength The mutation strength.
 */
void mutateGenome(VectDouble &genome, double mutationRate, double mutationStrength);

/**
 * @brief Mutates the entire population.
 * 
 * @param population The population of genomes.
 * @param mutationRate The mutation rate.
 * @param mutationStrength The mutation strength.
 */
void mutatePopulation(BoardDouble &population, double mutationRate, double mutationStrength);

#endif