#ifndef MINIPROJECT_PROBLEM_H
#define MINIPROJECT_PROBLEM_H
#include "vector"

using namespace std;

class Problem{
public:
    Problem() = default;
    virtual void openFile(const string& fileName){};
    virtual double evaluate(const vector<bool> &genotype) const = 0;
    virtual int getNumberOfItems() const = 0;
    ~Problem() = default;
};

#endif //MINIPROJECT_PROBLEM_H