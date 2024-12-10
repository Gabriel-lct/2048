#include "./include/GA.h"
#include "./include/AI.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"
#include <ncurses.h>

/********************* Part for the genetic algorithm *********************/

double runAi(const VectDouble &genome)
{
    int N = 4;
    int M = 4;
    int score = 0;
    Board board = genBoard(N, M);

    while (true)
    {
        int dir = findBestMove(board, score, 10, genome);
        if (dir == -1)
        {
            return score;
        }
        slide(board, dir, score, true);
    }
}

void displayBestGenome(VectDouble &genome, const int &index)
{
    printw("      Best genome n°%d: ", index);
    for (size_t i = 0; i < genome.size(); i++)
    {
        printw("%f", genome[i]);
        if (i != genome.size() - 1)
        {
            printw(", ");
        }
    }
    printw("\n");
    refresh();
}

int getBestGenome(VectDouble &fitnessScores)
{
    auto maxIt = std::max_element(fitnessScores.begin(), fitnessScores.end());
    return std::distance(fitnessScores.begin(), maxIt);
}

void runGeneticAlgorithm(BoardDouble &population, int &maxGamesPerGenome, int maxGenerations, double mutationRate, double mutationStrength)
{
    BoardDouble genomesEvolution;
    Vect fitnessScoresEvolution;
    for (int generation = 0; generation < maxGenerations; generation++)
    {
        printw("\n");
        printw("Génération %d\n", generation);
        printw("\n");
        refresh();

        // Etape 1 - Evaluation
        printw("  First step: Evaluation\n");
        printw("\n");
        refresh();
        VectDouble fitnessScores = evaluatePopulation(population, maxGamesPerGenome);
        printw("\n");
        refresh();

        printw("  Second step: Selection\n");
        refresh();
        // Etape 2 - Selection (20% of the current population)
        BoardDouble selectedGenomes = rouletteWheelSelection(population, fitnessScores, static_cast<int>(population.size() * 0.1));

        printw("\n");
        refresh();
        VectDouble bestGenome = population[getBestGenome(fitnessScores)];
        displayBestGenome(bestGenome, 1);
        genomesEvolution.push_back(bestGenome);

        printw("\n");
        printw("\n");
        refresh();
        printw("  Third step: Creation of the next generation\n");
        refresh();
        // Etape 3 - Create Next generation
        BoardDouble nextGeneration = createNextGeneration(selectedGenomes, population.size());

        printw("\n");
        refresh();
        printw("  Fourth step: Mutation of this very new generation\n");
        refresh();
        // Etape 4 - mutate next generation
        mutatePopulation(nextGeneration, mutationRate, mutationStrength);

        printw("\n");
        refresh();
        printw("  Fifth step: Replacement of the brand new generation\n");
        refresh();
        // remplacement de la nouvelle gen
        population = std::move(nextGeneration);

        printw("\n");
        printw("\n");
        refresh();
        double averageFitness = vectorAverage(fitnessScores);
        fitnessScoresEvolution.push_back(averageFitness);
        printw("  Génération %d : Fitness moyen = %f\n", generation, averageFitness);
        printw("\n");
        printw("\n");
        refresh();
    }

    // Display genomes evolution through generations
    printw("\n");
    printw("\n");
    refresh();
    for (BoardDouble::size_type i = 0; i < genomesEvolution.size(); i++)
    {
        printw("Generation n°%lu - average fitness score: %f - genomes : ", i, static_cast<double>(fitnessScoresEvolution[i]));
        for (VectDouble::size_type j = 0; j < genomesEvolution[i].size(); j++)
        {
            printw("%f, ", genomesEvolution[i][j]);
        }
        printw("\n");
        refresh();
    }
}

BoardDouble initializePopulationFromGenome(const VectDouble &firstGenome, int populationSize, double mutationRate)
{
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-mutationRate, mutationRate);

    // Initialize the population
    BoardDouble population;

    for (int i = 0; i < populationSize; ++i)
    {
        VectDouble genome = firstGenome;
        for (double &weight : genome)
        {
            weight += dis(gen); // Add random variation to each weight
        }
        population.push_back(genome);
    }

    return population;
}

double fitnessFunction(const VectDouble &genome, const int &numTrials, const int &genomeIndex)
{
    double totalScore = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 500);
    int sleepTime = dis(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    for (int i = 1; i <= numTrials; ++i)
    {
        double score = runAi(genome);
        totalScore += score;
    }
    printw("      Genome n°%d - Average score on %d tests: %f\n", genomeIndex, numTrials, totalScore / numTrials);
    refresh();
    return totalScore / numTrials;
}

VectDouble evaluatePopulation(const BoardDouble &population, int numTrials)
{
    VectDouble fitnessScores(population.size());

#pragma omp parallel for
    for (BoardDouble::size_type i = 0; i < population.size(); i++)
    {
        double fitness = fitnessFunction(population[i], numTrials, i + 1);
        fitnessScores[i] = fitness;
    }
    return fitnessScores;
}

BoardDouble rouletteWheelSelection(BoardDouble population, VectDouble fitnessScores, int numSelection)
{
    double probability = 0.0;
    // Select genomes
    BoardDouble selectedGenomes;

    while (selectedGenomes.size() < static_cast<size_t>(numSelection))
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double p = dis(gen);

        int index = 0;
        if (p < probability)
        {
            std::uniform_int_distribution<> dis2(0, population.size() - 1);
            index = dis2(gen);

            selectedGenomes.push_back(population[index]);
        }
        else
        {
            index = getBestGenome(fitnessScores);
            selectedGenomes.push_back(population[index]);
        }

        fitnessScores.erase(fitnessScores.begin() + index);
        population.erase(population.begin() + index);
    }

    return selectedGenomes;
}

GenomePair singlePointCrossover(const VectDouble &parent1, const VectDouble &parent2)
{
    auto genomeSize = parent1.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, genomeSize - 1); // Avoid 0 and genomeSize
    size_t crossoverPoint = dis(gen);

    VectDouble child1, child2;

    child1.insert(child1.end(), parent1.begin(), parent1.begin() + crossoverPoint);
    child1.insert(child1.end(), parent2.begin() + crossoverPoint, parent2.end());

    child2.insert(child2.end(), parent2.begin(), parent2.begin() + crossoverPoint);
    child2.insert(child2.end(), parent1.begin() + crossoverPoint, parent1.end());

    return {child1, child2};
}

BoardDouble createNextGeneration(const BoardDouble &selectedGenomes, int populationSize)
{
    BoardDouble NextGeneration;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, selectedGenomes.size() - 1);

    while (NextGeneration.size() < static_cast<size_t>(populationSize))
    {
        // Randomly select 2 parents
        const VectDouble &parent1 = selectedGenomes[dis(gen)];
        const VectDouble &parent2 = selectedGenomes[dis(gen)];

        auto [child1, child2] = singlePointCrossover(parent1, parent2);

        NextGeneration.push_back(child1);
        if (NextGeneration.size() < static_cast<size_t>(populationSize))
        {
            NextGeneration.push_back(child2);
        }
    }

    return NextGeneration;
}

void mutateGenome(VectDouble &genome, double mutationRate, double mutationStrength)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> mutationChance(0.0, 1.0);
    std::normal_distribution<> noise(0.0, mutationStrength);

    for (double &gene : genome)
    {
        if (mutationChance(gen) < mutationRate)
        {
            gene += gene * noise(gen);
        }
    }
}

void mutatePopulation(BoardDouble &population, double mutationRate, double mutationStrength)
{
    for (VectDouble &genome : population)
    {
        mutateGenome(genome, mutationRate, mutationStrength);
    }
}