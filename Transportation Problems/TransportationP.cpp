// in file 
/* 
rows col
one row
two row 
.
.
supply 
demand
*/
/*
example 
3 4
8 6 12 9
7 11 10 14
13 8 8 7
400 500 600
325 425 475 275
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

void readData(const string& filename, vector<vector<int>>& costMatrix, vector<int>& supply, vector<int>& demand) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    int rows, cols;
    file >> rows >> cols;

    if (rows > 4 || cols > 4) {
        cerr << "Error: Cannot process dimensions larger than 4x4!" << endl;
        exit(1); 
    }
    costMatrix.resize(rows, vector<int>(cols));
    supply.resize(rows);
    demand.resize(cols);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            file >> costMatrix[i][j];

    for (int i = 0; i < rows; ++i)
        file >> supply[i];

    for (int j = 0; j < cols; ++j)
        file >> demand[j];

    file.close();
}

int northWestCorner(const vector<vector<int>>& costMatrix, vector<int> supply, vector<int> demand) {
    int totalCost = 0;
    int rows = costMatrix.size();
    int cols = costMatrix[0].size();

    vector<vector<int>> allocation(rows, vector<int>(cols, 0));

    int i = 0, j = 0;
    while (i < rows && j < cols) {
        int allocate = min(supply[i], demand[j]);
        allocation[i][j] = allocate;
        totalCost += allocate * costMatrix[i][j];

        supply[i] -= allocate;
        demand[j] -= allocate;

        if (supply[i] == 0) ++i;
        if (demand[j] == 0) ++j;
    }

    return totalCost;
}

int leastCostMethod(const vector<vector<int>>& costMatrix, vector<int> supply, vector<int> demand) {
    int rows = costMatrix.size();
    int cols = costMatrix[0].size();
    int totalCost = 0;

    vector<vector<int>> allocation(rows, vector<int>(cols, 0));

    vector<vector<bool>> used(rows, vector<bool>(cols, false));

    while (true) {
        int minCost = numeric_limits<int>::max();
        int minRow = -1, minCol = -1;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (!used[i][j] && costMatrix[i][j] < minCost) {
                    minCost = costMatrix[i][j];
                    minRow = i;
                    minCol = j;
                }
            }
        }

        if (minRow == -1 || minCol == -1)
            break;

        int allocate = min(supply[minRow], demand[minCol]);
        allocation[minRow][minCol] = allocate;
        totalCost += allocate * costMatrix[minRow][minCol];

        supply[minRow] -= allocate;
        demand[minCol] -= allocate;

        if (supply[minRow] == 0) {
            for (int j = 0; j < cols; ++j) {
                used[minRow][j] = true;
            }
        }
        if (demand[minCol] == 0) {
            for (int i = 0; i < rows; ++i) {
                used[i][minCol] = true;
            }
        }
    }

    return totalCost;
}

int vogelsApproximation(const vector<vector<int>>& costMatrix, vector<int> supply, vector<int> demand) {
    int rows = costMatrix.size();
    int cols = costMatrix[0].size();
    int totalCost = 0;

    vector<vector<int>> allocation(rows, vector<int>(cols, 0));

    auto calculatePenalties = [&](const vector<vector<int>>& costMatrix, const vector<bool>& rowUsed, const vector<bool>& colUsed, vector<int>& rowPenalties, vector<int>& colPenalties) {
        for (int i = 0; i < rows; ++i) {
            if (rowUsed[i]) {
                rowPenalties[i] = -1; 
                continue;
            }
            int firstMin = numeric_limits<int>::max(), secondMin = numeric_limits<int>::max();
            for (int j = 0; j < cols; ++j) {
                if (colUsed[j]) continue; 
                if (costMatrix[i][j] < firstMin) {
                    secondMin = firstMin;
                    firstMin = costMatrix[i][j];
                }
                else if (costMatrix[i][j] < secondMin) {
                    secondMin = costMatrix[i][j];
                }
            }
            rowPenalties[i] = secondMin - firstMin;
        }

        for (int j = 0; j < cols; ++j) {
            if (colUsed[j]) {
                colPenalties[j] = -1; 
                continue;
            }
            int firstMin = numeric_limits<int>::max(), secondMin = numeric_limits<int>::max();
            for (int i = 0; i < rows; ++i) {
                if (rowUsed[i]) continue; 
                if (costMatrix[i][j] < firstMin) {
                    secondMin = firstMin;
                    firstMin = costMatrix[i][j];
                }
                else if (costMatrix[i][j] < secondMin) {
                    secondMin = costMatrix[i][j];
                }
            }
            colPenalties[j] = secondMin - firstMin; 
        }
        };

    vector<bool> rowUsed(rows, false), colUsed(cols, false);

    while (true) {
        vector<int> rowPenalties(rows), colPenalties(cols);
        calculatePenalties(costMatrix, rowUsed, colUsed, rowPenalties, colPenalties);

        int maxPenalty = -1;
        int isRow = 0; 
        int maxIndex = -1;

        for (int i = 0; i < rows; ++i) {
            if (rowPenalties[i] > maxPenalty) {
                maxPenalty = rowPenalties[i];
                isRow = 1;
                maxIndex = i;
            }
        }
        for (int j = 0; j < cols; ++j) {
            if (colPenalties[j] > maxPenalty) {
                maxPenalty = colPenalties[j];
                isRow = 0;
                maxIndex = j;
            }
        }

        if (maxPenalty == -1) break;

        int allocate = 0;
        if (isRow) {
            int minCol = -1, minCost = numeric_limits<int>::max();
            for (int j = 0; j < cols; ++j) {
                if (colUsed[j]) continue;
                if (costMatrix[maxIndex][j] < minCost) {
                    minCost = costMatrix[maxIndex][j];
                    minCol = j;
                }
            }
            allocate = min(supply[maxIndex], demand[minCol]);
            allocation[maxIndex][minCol] = allocate;
            totalCost += allocate * costMatrix[maxIndex][minCol];
            supply[maxIndex] -= allocate;
            demand[minCol] -= allocate;
            if (supply[maxIndex] == 0) rowUsed[maxIndex] = true;
            if (demand[minCol] == 0) colUsed[minCol] = true;
        }
        else {
            int minRow = -1, minCost = numeric_limits<int>::max();
            for (int i = 0; i < rows; ++i) {
                if (rowUsed[i]) continue;
                if (costMatrix[i][maxIndex] < minCost) {
                    minCost = costMatrix[i][maxIndex];
                    minRow = i;
                }
            }
            allocate = min(supply[minRow], demand[maxIndex]);
            allocation[minRow][maxIndex] = allocate;
            totalCost += allocate * costMatrix[minRow][maxIndex];
            supply[minRow] -= allocate;
            demand[maxIndex] -= allocate;
            if (supply[minRow] == 0) rowUsed[minRow] = true;
            if (demand[maxIndex] == 0) colUsed[maxIndex] = true;
        }
    }

    return totalCost;
}

int main() {
    vector<vector<int>> costMatrix;
    vector<int> supply, demand;

    string filename = "data.txt";
    readData(filename, costMatrix, supply, demand);

    vector<int> supplyCopy = supply;
    vector<int> demandCopy = demand;

    int nwCost = northWestCorner(costMatrix, supplyCopy, demandCopy);
    cout << "North-West Corner Cost: " << nwCost << endl;

    supplyCopy = supply;  
    demandCopy = demand;
    int lcCost = leastCostMethod(costMatrix, supplyCopy, demandCopy);
    cout << "Least Cost Method Cost: " << lcCost << endl;

    supplyCopy = supply; 
    demandCopy = demand;
    int vamCost = vogelsApproximation(costMatrix, supplyCopy, demandCopy);
    cout << "Vogel's Approximation Cost: " << vamCost << endl;

    return 0;
}
