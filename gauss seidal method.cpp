#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& initialGuess, double tolerance = 1e-6, int maxIterations = 100) {
    int n = A.size();
    vector<double> x = initialGuess;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        vector<double> xOld = x; // Store the previous iteration's values for convergence check

        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    sum += A[i][j] * x[j]; // Use updated x values immediately
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        // Check for convergence
        double maxDiff = 0;
        for (int i = 0; i < n; ++i) {
            maxDiff = max(maxDiff, abs(x[i] - xOld[i]));
        }

        if (maxDiff < tolerance) {
            cout << "Converged after " << iteration + 1 << " iterations." << endl;
            return x;
        }
    }

    cout << "Gauss-Seidel method did not converge within the maximum number of iterations." << endl;
    return x; // Return the last approximation
}

int main() {
    int n;
    cout << "Enter the number of equations (n): ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    vector<double> initialGuess(n, 0.0); // Initial guess of all zeros

    cout << "Enter the coefficient matrix A:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the result vector b:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    cout << "Enter initial guess (optional, defaults to 0.0):" << endl;
    char response;
    cout << "Use default initial guess? (y/n): ";
    cin >> response;
    if (response == 'n' || response == 'N'){
        for (int i = 0; i < n; i++){
            cout << "x" << i+1 << " = ";
            cin >> initialGuess[i];
        }
    }

    vector<double> solution = gaussSeidel(A, b, initialGuess);

    cout << "Solution:" << endl;
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }

    return 0;
}
