#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include <random>
#include "iostream"

int main(){
    random_device rnd;
    std::mt19937 randomGenerator(rnd());

    try {
        cout << "Knapsack Problem read from file:" << endl;
        KnapsackProblem knapsackProblem2;
        knapsackProblem2.openFile(R"(C:\Users\kacpi\OneDrive\Pulpit\knapsackInput.txt)");
        GeneticAlgorithm geneticAlgorithm2(100, 0.08, 0.5);
        geneticAlgorithm2.solveProblem(knapsackProblem2, 100, randomGenerator);
        geneticAlgorithm2.showFittest();


        cout << "\n\n" << "Knapsack Problem from constructor:" << endl;
        KnapsackProblem knapsackProblem(10, 30, {25, 19, 15, 5, 46, 21, 2, 58, 18, 6}, {7, 7, 6, 9, 3, 10, 8, 5, 8, 5});
        GeneticAlgorithm geneticAlgorithm(20, 0.1, 0.5);
        geneticAlgorithm.solveProblem(knapsackProblem, 100, randomGenerator);
        geneticAlgorithm.showFittest();
    }
    catch (std::exception& exception) {
        exception.what();
    }
    catch (std::runtime_error& exception) {
        exception.what();
    }
    return 0;
}
