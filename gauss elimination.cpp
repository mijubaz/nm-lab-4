#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to perform forward elimination
void forwardElimination(vector<vector<double>>& augmentedMatrix, int n) {
    for (int i = 0; i < n; i++) {
        // Searching for maximum in this column
        double maxEl = abs(augmentedMatrix[i][i]);
        int row = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(augmentedMatrix[k][i]) > maxEl) {
                maxEl = abs(augmentedMatrix[k][i]);
                row = k;
            }
        }

        // Swap maximum row with current row
        for (int k = i; k < n + 1; k++) {
            swap(augmentedMatrix[row][k], augmentedMatrix[i][k]);
        }

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            double factor = augmentedMatrix[k][i] / augmentedMatrix[i][i];
            for (int j = i; j < n + 1; j++) {
                augmentedMatrix[k][j] -= augmentedMatrix[i][j] * factor;
            }
        }
    }
}

// Function to perform back substitution
vector<double> backSubstitution(const vector<vector<double>>& augmentedMatrix, int n) {
    vector<double> solution(n);
    for (int i = n - 1; i >= 0; i--) {
        solution[i] = augmentedMatrix[i][n]; // Last column is the result column
        for (int j = i + 1; j < n; j++) {
            solution[i] -= augmentedMatrix[i][j] * solution[j];
        }
        solution[i] /= augmentedMatrix[i][i];
    }
    return solution;
}

int main() {
    int n;
    cout << "Enter the number of variables (n): ";
    cin >> n;

    vector<vector<double>> augmentedMatrix(n, vector<double>(n + 1));

    // Input augmented matrix (n x n + 1)
    cout << "Enter the augmented matrix (n x n + 1):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cin >> augmentedMatrix[i][j];
        }
    }

    // Forward Elimination
    forwardElimination(augmentedMatrix, n);

    // Back Substitution
    vector<double> solution = backSubstitution(augmentedMatrix, n);

    // Output the solution
    cout << "\nThe solution is:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << solution[i] << endl;
    }

    return 0;
}

