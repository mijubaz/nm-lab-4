#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to perform Gauss-Jordan elimination
vector<double> gaussJordan(vector<vector<double>>& matrix) {
    int n = matrix.size();

    // Augmented matrix: Combine coefficient matrix and result vector
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Nothing to do, it is already augmented.
        }
    }

    // Forward Elimination
    for (int i = 0; i < n; i++) {
        // Find pivot
        int pivotRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(matrix[k][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = k;
            }
        }

        // Swap rows if necessary
        if (pivotRow != i) {
            swap(matrix[i], matrix[pivotRow]);
        }

        // Check for zero pivot (singular matrix)
        if (abs(matrix[i][i]) < 1e-10) {
            cerr << "Matrix is singular or nearly singular." << endl;
            return vector<double>(); // Return an empty vector to indicate failure
        }

        // Make pivot element 1
        double pivot = matrix[i][i];
        for (int j = 0; j <= n; j++) {
            matrix[i][j] /= pivot;
        }

        // Eliminate other elements in the column
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j <= n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    // Extract the solution vector
    vector<double> solution(n);
    for (int i = 0; i < n; i++) {
        solution[i] = matrix[i][n];
    }

    return solution;
}

int main() {
    int n;

    cout << "Enter the number of equations (n): ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n + 1)); // Augmented matrix (n x n+1)

    cout << "Enter the augmented matrix (coefficients and constants):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<double> solution = gaussJordan(matrix);

    if (!solution.empty()) {
        cout << "Solution:" << endl;
        cout << fixed << setprecision(6); // Set precision for output
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
    } else {
        cout << "No unique solution found." << endl;
    }

    return 0;
}
