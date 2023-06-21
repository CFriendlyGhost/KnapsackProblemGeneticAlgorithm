#ifndef MINIPROJECT_CGENETICALGORITHM_H
#define MINIPROJECT_CGENETICALGORITHM_H
#include <vector>
#include "Individual.h"

class GeneticAlgorithm {
private:
    int populationSize;
    double mutationProbability;
    double crossoverProbability;
    vector<Individual> population;
    vector<Individual> nextGeneration;
    Individual fittestGenotype;
    double bestFitness;

public:
    GeneticAlgorithm(int populationSize, double mutationProbability, double crossoverProbability);
    void generatePopulation(const Problem &problem);
    void reproduce(const Problem &problem, mt19937 &random);
    int findParentIndex(const Problem &problem, mt19937 &random) const;
    int getFittest(const Problem &problem);
    void solveProblem(const Problem &problem, int numberOfGenerations, mt19937 &random);
    int tournament(int gladiator1Index, int gladiator2Index, const Problem &problem) const;
    void showFittest();
    ~GeneticAlgorithm() = default;
};

#endif //MINIPROJECT_CGENETICALGORITHM_H