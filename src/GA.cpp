#include "./include/GA.h"
#include "./include/AI.h"
#include "./include/Utils.h"
#include "./include/Game.h"
#include "./include/Display.h"

/********************* Part for the genetic algorithm *********************/

double runAi(const VectDouble &genome)
{
    int N = 4;
    int M = 4;
    int score = 0;
    Board board = genBoard(N, M);

    while (true)
    {
        int c = 0;
        int dir = findBestMove(board, score, 6, genome);
        if (dir == -1)
        {
            return score;
        }
        slide(board, dir, score, c);
        spawn(board, c);
    }
}

void runGeneticAlgorithm(BoardDouble &population, int &maxGamesPerGenome, int maxGenerations, double mutationRate, double mutationStrength)
{
    for (int generation = 0; generation < maxGenerations; generation++)
    {
        // Etape 1 - Evaluation
        std::cout << "First step: Evaluation" << std::endl;
        VectDouble fitnessScores = evaluatePopulation(population, maxGamesPerGenome);

        std::cout << "Second step: Selection" << std::endl;
        // Etape 2 - Selection (20% of the current population)
        BoardDouble selectedGenomes = rouletteWheelSelection(population, fitnessScores, static_cast<int>(population.size() * 0.2));

        std::cout << "Third step: Creation of the next generation" << std::endl;
        // Etape 3 - Create Next generation
        BoardDouble nextGeneration = createNextGeneration(selectedGenomes, population.size());

        std::cout << "Fourth step: Mutation of this very new generation" << std::endl;
        // Etape 4 - mutate next generation
        mutatePopulation(nextGeneration, mutationRate, mutationStrength);

        std::cout << "Fifth step: Replacement of the brand new generation" << std::endl;
        // remplacement de la nouvelle gen
        population = std::move(nextGeneration);

        double bestFitness = *std::max_element(fitnessScores.begin(), fitnessScores.end());
        std::cout << "Génération " << generation << " : Meilleur fitness = " << bestFitness << std::endl;
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
        VectDouble genome = firstGenome; // Start with the basic genome
        for (double &weight : genome)
        {
            weight += dis(gen); // Add random variation to each weight
        }
        population.push_back(genome); // Add genome to the population
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
        std::cout << "      Genome n°" << genomeIndex << " - Test n°" << i << "/" << numTrials;
        std::cout << " - Score: " << score << std::endl;
        totalScore += score;
    }
    std::cout << std::endl;
    std::cout << "      Genome n°" << genomeIndex << " - Average score on " << numTrials << " tests: " << totalScore / numTrials << std::endl;
    std::cout << std::endl;
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
    std::cout << std::endl;
    std::cout << "      All fitness scores :" << std::endl;
    for (VectDouble::size_type i = 0; i < fitnessScores.size(); i++)
    {
        std::cout << "      Genome n°" << i + 1 << " - FitnessScore : " << fitnessScores[i] << std::endl;
    }
    std::cout << std::endl;
    return fitnessScores;
}

BoardDouble rouletteWheelSelection(const BoardDouble &population, VectDouble &fitnessScores, int numSelection)
{
    double totalFitness = 0;
    for (double fitness : fitnessScores)
    {
        totalFitness += fitness;
    }

    // Normalize the fitness scores to probabilities
    VectDouble probabilities;
    for (double fitness : fitnessScores)
    {
        probabilities.push_back(fitness / totalFitness);
    }

    VectDouble cumulativeProbabilities;
    double cumulative = 0.0;
    for (double probability : probabilities)
    {
        cumulative += probability;
        cumulativeProbabilities.push_back(cumulative);
    }

    // Select genomes
    std::vector<std::vector<double>> selectedGenomes;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    while (selectedGenomes.size() < static_cast<size_t>(numSelection))
    {
        double randomValue = dis(gen);
        for (size_t j = 0; j < cumulativeProbabilities.size(); j++)
        {
            if (randomValue <= cumulativeProbabilities[j])
            {
                selectedGenomes.push_back(population[j]);
                break;
            }
        }
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
            gene += noise(gen);
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