#include "KnapsackProblem.h"
#include "iostream"
#include "fstream"

using namespace std;

KnapsackProblem::KnapsackProblem() {
    numberOfItems = 0;
    weightLimit = 0;
}

KnapsackProblem::KnapsackProblem(int _numberOfItems, double _weightLimit, const vector<double> &_values,
                                 const vector<double> &_weight) {

    if (_numberOfItems <= 0 || _weightLimit < 0 || checkVectorData(_values) || checkVectorData(_weight)) {
        throw runtime_error("Inappropriate values in knapsack");
    }

    numberOfItems = _numberOfItems;
    weightLimit = _weightLimit;
    values = _values;
    weight = _weight;
}

void KnapsackProblem::openFile(const string &fileName) {
    fstream fileStream;

    try {
        fileStream.open(fileName);

        if (fileStream.fail()) {
            throw std::ios::failure("The file does not exist!");
        }
        else {
            fileStream >> numberOfItems >> weightLimit;
            if (numberOfItems <= 0 || weightLimit <= 0) {
                throw std::ios::failure("Bad date in file (number of items or weight limit)!");
            }

            values.reserve(numberOfItems);
            weight.reserve(numberOfItems);
            double currentWeight;
            double currentValue;

            for (int i = 0; i < numberOfItems; ++i) {
                fileStream >> currentValue >> currentWeight;
                if (currentWeight < 0 || currentValue < 0) {
                    throw std::ios::failure("Bad date in file (weight or value)!");
                }
                weight.push_back(currentWeight);
                values.push_back(currentValue);
            }
        }
        fileStream.close();
    }
    catch (const exception &exception) {
        cout << exception.what() << endl;
    }
}

double KnapsackProblem::evaluate(const vector<bool> &genotype) const {
    double fitness = 0;
    double totalWeight = 0;

    for (int i = 0; i < genotype.size(); ++i) {
        if (genotype[i]) {
            totalWeight += weight[i];
            fitness += values[i];
        }
    }

    if (totalWeight > weightLimit) {
        fitness = 0;
    }

    return fitness;
}

int KnapsackProblem::getNumberOfItems() const {
    return numberOfItems;
}

bool KnapsackProblem::checkVectorData(vector<double> toCheck) {
    for (int i = 0; i < toCheck.size(); ++i) {
        if (toCheck[i] < 0) return true;
    }

    return false;
}

KnapsackProblem::KnapsackProblem(KnapsackProblem &&other) noexcept {
    numberOfItems = other.numberOfItems;
    weightLimit = other.weightLimit;
    weight = std::move(other.weight);
    values = std::move(other.values);
}

KnapsackProblem &KnapsackProblem::operator=(KnapsackProblem &&other) noexcept {
    if (this != &other) {
        numberOfItems = other.numberOfItems;
        weightLimit = other.weightLimit;
        values = std::move(other.values);
        weight = std::move(other.weight);
    }

    return *this;
}
