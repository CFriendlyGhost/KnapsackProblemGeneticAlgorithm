#include "GeneticAlgorithm.h"
#include <random>
#include "iostream"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(int popSize, double mutProbability, double crossProbability) {

    if (popSize <= 0 || mutProbability < 0 || crossProbability < 0) {
        throw runtime_error("Inappropriate value to generate population");
    }

    populationSize = popSize;
    mutationProbability = mutProbability;
    crossoverProbability = crossProbability;
    population.reserve(populationSize);
    bestFitness = 0;
}

void GeneticAlgorithm::generatePopulation(const Problem &problem) {
    for (int i = 0; i < populationSize; ++i) {
        Individual individual(problem.getNumberOfItems());
        individual.generateChromosome();
        population.push_back(std::move(individual));
    }
}

void GeneticAlgorithm::reproduce(const Problem &problem, mt19937 &random) {
    uniform_real_distribution<double> distribution(0, 1);
    nextGeneration.reserve(populationSize);

    for (int i = 0; i < (populationSize / 2) + 1; ++i) {
        Individual parent1 = population[findParentIndex(problem, random)];
        Individual parent2 = population[findParentIndex(problem, random)];

        if (distribution(random) < crossoverProbability) {
            parent1.crossover(parent2, random);
        }

        parent1.mutate(mutationProbability, random);
        parent2.mutate(mutationProbability, random);

        if (i < populationSize / 2) {                                                  //zgodnie z poleceniem, dwójka rodziców ma posiadać dwójkę dzieci
            nextGeneration.push_back(std::move(parent1));                          //nie jest jednak niedopuszczalne tworzenie populacji o nieparzystej
            nextGeneration.push_back(std::move(parent2));                          //liczbie członków więc należy zabezpieczyć się przed takim przypadkiem
        }
        else if (populationSize % 2 == 1) {
            nextGeneration.push_back(std::move(parent1));
        }
    }

    for (int i = 0; i < populationSize; ++i) {
        population[i] = std::move(nextGeneration[i]);
    }

    nextGeneration.clear();
}

int GeneticAlgorithm::getFittest(const Problem &problem) {
    double bestGenFitness = 0;
    int indexOfFittest = -1;

    for (int i = 0; i < populationSize; ++i) {
        double actualFitness = population[i].fitness(problem);

        if (actualFitness > bestGenFitness) {
            bestGenFitness = actualFitness;
            indexOfFittest = i;
        }
    }
    return indexOfFittest;
}

int GeneticAlgorithm::findParentIndex(const Problem &problem, mt19937 &random) const {
    uniform_int_distribution<int> dist(0, populationSize - 1);

    return tournament(dist(random), dist(random), problem);
}

int GeneticAlgorithm::tournament(int gladiator1Index, int gladiator2Index, const Problem &problem) const {

    if (population[gladiator1Index].fitness(problem) > population[gladiator2Index].fitness(problem)) {
        return gladiator1Index;
    } else return gladiator2Index;
}

void GeneticAlgorithm::solveProblem(const Problem &problem, int numberOfGenerations, mt19937 &random) {
    generatePopulation(problem);
                                                                                        //zabezpieczenie przed sytuacją
    if (getFittest(problem) != -1) {                                                    //kiedy algorytm moglbym
        fittestGenotype = population[getFittest(problem)];                              //miec problem z znalezieniem
        bestFitness = fittestGenotype.fitness(problem);                                 //jakiegokolwiek osobnika z
    }                                                                                   //wagą mniejszą od maksymalnej

    while (numberOfGenerations != 0) {
        reproduce(problem, random);
        numberOfGenerations--;

        if (getFittest(problem) != -1) {
            Individual currentFittest = population[getFittest(problem)];

            if (currentFittest.fitness(problem) > bestFitness) {
                bestFitness = currentFittest.fitness(problem);
                fittestGenotype = std::move(currentFittest);
            }
        }
    }
}

void GeneticAlgorithm::showFittest() {
    if (bestFitness > 0) {
        cout << "Best genotype's fitness from all generations: " << bestFitness << endl;
        cout << "It looks as follow: " << endl;
        fittestGenotype.showChromosome();
    } else {
        cout << "Algorithm failed to find the best result :(";
    }
}
