#ifndef MINIPROJECT_INDIVIDUAL_H
#define MINIPROJECT_INDIVIDUAL_H
#include <vector>
#include <random>
#include "KnapsackProblem.h"
using namespace std;


class Individual {
private:
    vector<bool> chromosome;
    int size;

public:
    Individual() { size = 0; }
    explicit Individual(int size);
    Individual(Individual &&other) noexcept;
    Individual(const Individual &other) = default;
    ~Individual()= default;
    double fitness(const Problem &problem) const;
    void mutate(double mutProbability, mt19937& random);
    void crossover(Individual &secondChromosome, mt19937& random);
    void generateChromosome();
    Individual& operator=(Individual&& other) noexcept;
    Individual& operator=(const Individual& other) = default;
    void showChromosome();
};


#endif //MINIPROJECT_INDIVIDUAL_H