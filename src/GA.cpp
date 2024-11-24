#include "./include/GA.h"
#include "./include/AI.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

/********************* Part for the genetic algorithm *********************/

const double variationRange = 0.1;                   // Example value, adjust as needed
const VectDouble basicGenome = {0.5, 0.5, 0.5, 0.5}; // Example values, adjust as needed

double runAi(VectDouble genome)
{
    int N = 4;
    int M = 4;
    int score = 0;
    Board board = genBoard(N, M);

    while (true)
    {
        std::cout << "Currently generating with ai... Current score: " << score << std::endl;
        int c = 0;
        int dir = findBestMove(board, score, 6, genome);
        if (dir == -1)
        {
            displayBoard(board);
            std::cout << "Game over!" << std::endl;
            return score;
        }
        slide(board, dir, score, c);
        spawn(board, c);
    }
}

BoardDouble initializePopulationFromGenome(const VectDouble &genome, int populationSize, double mutationRate)
{
    // Random number generator
    std::random_device rd;                                                 // Seed
    std::mt19937 gen(rd());                                                // Random engine
    std::uniform_real_distribution<> dis(-variationRange, variationRange); // Variation range

    // Initialize the population
    BoardDouble population;

    for (int i = 0; i < populationSize; ++i)
    {
        VectDouble genome = basicGenome; // Start with the basic genome
        for (double &weight : genome)
        {
            weight += dis(gen); // Add random variation to each weight
        }
        population.push_back(genome); // Add genome to the population
    }

    return population;
}

double fitnessFunction(const VectDouble &genome, const int &numTrials)
{
    // Run the game multiple times with the given weights
    double averageScore = 0;
    for (int i = 0; i < numTrials; ++i)
    {
        double score = runAi(genome);
        std::cout << score << "  -   " << std::endl;
        averageScore += score;
    }
    return averageScore / numTrials;
}

VectDouble evaluatePopulation(const BoardDouble &population, int numTrials = 5)
{
    VectDouble fitnessScores;
    for (const auto &genome : population)
    {
        double fitness = fitnessFunction(genome, numTrials);
        fitnessScores.push_back(fitness);
    }
    return fitnessScores;
}
