#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to multiply a matrix by a vector
vector<double> matrixVectorMultiply(const vector<vector<double>>& matrix, const vector<double>& vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<double> result(rows, 0.0);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

// Function to find the norm (magnitude) of a vector
double vectorNorm(const vector<double>& vector) {
    double sum = 0.0;
    for (double val : vector) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Power method to find the dominant eigenvalue
pair<double, vector<double>> powerMethod(const vector<vector<double>>& matrix, vector<double> initialVector, double tolerance = 1e-6, int maxIterations = 1000) {
    int n = matrix.size();
    vector<double> x = initialVector;
    double eigenvalue = 0.0;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        vector<double> Ax = matrixVectorMultiply(matrix, x);
        double newEigenvalue = vectorNorm(Ax);
        vector<double> newX(n);

        // Normalize the vector
        for (int i = 0; i < n; ++i) {
            newX[i] = Ax[i] / newEigenvalue;
        }

        // Check for convergence
        if (abs(newEigenvalue - eigenvalue) < tolerance) {
            cout << "Converged after " << iteration + 1 << " iterations." << endl;
            return make_pair(newEigenvalue, newX);
        }

        eigenvalue = newEigenvalue;
        x = newX;
    }

    cout << "Power method did not converge within the maximum number of iterations." << endl;
    return make_pair(eigenvalue, x); // Return the last approximation
}

int main() {
    int n;
    cout << "Enter the size of the square matrix (n): ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    vector<double> initialVector(n, 1.0); // Initial vector of all 1s

    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "Enter initial vector (optional, defaults to 1.0):" << endl;
    char response;
    cout << "Use default initial vector? (y/n): ";
    cin >> response;
    if (response == 'n' || response == 'N'){
        for (int i = 0; i < n; i++){
            cout << "x" << i+1 << " = ";
            cin >> initialVector[i];
        }
    }

    pair<double, vector<double>> result = powerMethod(matrix, initialVector);

    cout << "Dominant Eigenvalue: " << fixed << setprecision(6) << result.first << endl;
    cout << "Corresponding Eigenvector: ";
    for (double val : result.second) {
        cout << fixed << setprecision(6) << val << " ";
    }
    cout << endl;

    return 0;
}
