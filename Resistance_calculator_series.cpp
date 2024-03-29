#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class ResistorCalculator {
private:
    vector<double> resistances;
    vector<string> seriesResults;
    vector<string> parallelResults;

public:
    ResistorCalculator(const vector<double>& r) : resistances(r) {}

    double calculateParallelResistance(const vector<double>& resistors) {
        double totalInverseResistance = 0.0;
        for (double resistance : resistors) {
            totalInverseResistance += 1.0 / resistance;
        }
        return 1.0 / totalInverseResistance;
    }

    void findSeriesCombinations(double desiredResistance) {
        seriesResults.clear();
        bool found = false;

        cout << "Combinations of up to four resistors in series to achieve " << desiredResistance << " ohms:" << endl;

        sort(resistances.begin(), resistances.end());

        size_t n = resistances.size();
        for (size_t i = 0; i < n; ++i) {
            double sum1 = resistances[i];
            if (sum1 == desiredResistance) {
                seriesResults.push_back(to_string(resistances[i]));
                found = true;
            }
            for (size_t j = i + 1; j < n; ++j) {
                double sum2 = sum1 + resistances[j];
                if (sum2 == desiredResistance) {
                    seriesResults.push_back(to_string(resistances[i]) + " + " + to_string(resistances[j]));
                    found = true;
                }
                for (size_t k = j + 1; k < n; ++k) {
                    double sum3 = sum2 + resistances[k];
                    if (sum3 == desiredResistance) {
                        seriesResults.push_back(to_string(resistances[i]) + " + " + to_string(resistances[j]) + " + " + to_string(resistances[k]));
                        found = true;
                    }
                    for (size_t l = k + 1; l < n; ++l) {
                        double sum4 = sum3 + resistances[l];
                        if (sum4 == desiredResistance) {
                            seriesResults.push_back(to_string(resistances[i]) + " + " + to_string(resistances[j]) + " + " + to_string(resistances[k]) + " + " + to_string(resistances[l]));
                            found = true;
                        }
                    }
                }
            }
        }

        if (!found) {
            seriesResults.push_back("No combination found");
        }
    }

    void findParallelCombinations(double desiredResistance) {
        parallelResults.clear();
        bool found = false;
        const double tolerance = 1e-6;

        cout << "Parallel combinations to achieve " << desiredResistance << " ohms:" << endl;

        for (size_t i = 0; i < resistances.size(); ++i) {
            for (size_t j = i + 1; j < resistances.size(); ++j) {
                double parallelSum2 = calculateParallelResistance({resistances[i], resistances[j]});
                if (abs(parallelSum2 - desiredResistance) < tolerance) {
                    parallelResults.push_back("(" + to_string(resistances[i]) + " || " + to_string(resistances[j]) + ")");
                    found = true;
                }
                for (size_t k = j + 1; k < resistances.size(); ++k) {
                    double parallelSum3 = calculateParallelResistance({resistances[i], resistances[j], resistances[k]});
                    if (abs(parallelSum3 - desiredResistance) < tolerance) {
                        parallelResults.push_back("(" + to_string(resistances[i]) + " || " + to_string(resistances[j]) + " || " + to_string(resistances[k]) + ")");
                        found = true;
                    }
                    for (size_t l = k + 1; l < resistances.size(); ++l) {
                        double parallelSum4 = calculateParallelResistance({resistances[i], resistances[j], resistances[k], resistances[l]});
                        if (abs(parallelSum4 - desiredResistance) < tolerance) {
                            parallelResults.push_back("(" + to_string(resistances[i]) + " || " + to_string(resistances[j]) + " || " + to_string(resistances[k]) + " || " + to_string(resistances[l]) + ")");
                            found = true;
                        }
                    }
                }
            }
        }

        if (!found) {
            parallelResults.push_back("No combination found");
        }
    }

    void combineResults(double desiredResistance) {
        cout << "Combinations of resistors to achieve " << desiredResistance << " ohms:" << endl;
        for (const string& series : seriesResults) {
            for (const string& parallel : parallelResults) {
                cout << "Series: " << series << " | Parallel: " << parallel << endl;
            }
        }
    }
};

int main() {
    vector<double> resistances = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4,
                                  2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2,
                                  6.8, 7.5, 8.2, 9.1};

    ResistorCalculator calculator(resistances);

    char choice;
    do {
        double desiredResistance;
        cout << "Enter a desired resistance value: ";
        cin >> desiredResistance;

        calculator.findSeriesCombinations(desiredResistance);
        calculator.findParallelCombinations(desiredResistance);
        calculator.combineResults(desiredResistance);

        cout << "Do you want to calculate another resistance? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
