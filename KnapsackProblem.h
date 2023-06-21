#ifndef MINIPROJECT_CKNAPSACKPROBLEM_H
#define MINIPROJECT_CKNAPSACKPROBLEM_H
#include <vector>
#include <string>
#include "Problem.h"
using namespace std;

class KnapsackProblem : public virtual Problem{
private:
    int numberOfItems;
    double weightLimit;
    vector<double> values;
    vector<double> weight;
    static bool checkVectorData(vector<double> toCheck);

public:
    KnapsackProblem();
    KnapsackProblem(KnapsackProblem&& other) noexcept;
    KnapsackProblem(const KnapsackProblem& other) = default;
    KnapsackProblem(int numberOfItems, double weightLimit, const vector<double> &values, const vector<double> &weight);
    void openFile(const string& fileName) override;
    double evaluate(const vector<bool>& genotype) const override;
    int getNumberOfItems() const override;
    KnapsackProblem& operator=(KnapsackProblem&& other) noexcept;
    KnapsackProblem& operator=(const KnapsackProblem& other) = default;
};


#endif //MINIPROJECT_CKNAPSACKPROBLEM_H
