#include "Individual.h"
#include <random>
#include <iostream>
using namespace std;

Individual::Individual(int size) : size(size) {
    chromosome.resize(size);
}

Individual::Individual(Individual &&other) noexcept {
    chromosome = std::move(other.chromosome);
    size = other.size;
}

double Individual::fitness(const Problem &problem) const {
    return problem.evaluate(chromosome);
}

void Individual::mutate(double mutProbability, mt19937& random) {
    uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < size; ++i) {
        if(dist(random) < mutProbability){
            chromosome[i] = ~chromosome[i];
        }
    }
}

void Individual::crossover(Individual &secondChromosome, mt19937& random) {
    uniform_int_distribution<int> dist(0, size - 1);
    int crossingPoint = dist(random);

    for (int i = 0; i < size; ++i) {
        if(crossingPoint <= i){
            bool temp = secondChromosome.chromosome[i];
            secondChromosome.chromosome[i] = chromosome[i];
            chromosome[i] = temp;
        }
    }
}

void Individual::generateChromosome() {
    default_random_engine rnd{std::random_device{}()};
    uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < size; ++i) {
        if(dist(rnd) > 0.5)
            chromosome[i] = true;                               //resize uzywa konstruktora domyslnego, wiec nie trzeba wpisywac false
    }
}

Individual& Individual::operator=(Individual &&other) noexcept{
    if(this != &other){
        chromosome = std::move(other.chromosome);
        size = other.size;
    }

    return *this;
}

void Individual::showChromosome() {
    cout << "[";

    for (int i = 0; i < chromosome.size(); ++i) {
        cout << chromosome[i] << " ";
    }

    cout << "]";
}
