#include "matrix_utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printMatrix(const Matrix& A, const string& label) {
    cout << "\n" << label << ":\n";
    int rows = A.size();
    int cols = A[0].size();
    for (int i = 0; i < rows; i++) {
        cout << "  [ ";
        for (int j = 0; j < cols; j++)
            cout << setw(10) << fixed << setprecision(4) << A[i][j] << " ";
        cout << "]\n";
    }
}

void printVector(const vector<double>& v, const string& label) {
    cout << "\n" << label << ":\n";
    for (int i = 0; i < (int)v.size(); i++)
        cout << "  x[" << i + 1 << "] = "
             << fixed << setprecision(6) << v[i] << "\n";
}

Matrix inputMatrix(int rows, int cols, const string& name) {
    cout << "\nEnter elements of " << name
         << " (" << rows << "x" << cols << "):\n";

    Matrix M(rows, vector<double>(cols));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            cout << "  " << name << "["
                 << i + 1 << "][" << j + 1 << "] = ";
            cin >> M[i][j];
        }
    return M;
}

vector<double> inputVector(int n, const string& name) {
    cout << "\nEnter elements of " << name
         << " (" << n << " values):\n";

    vector<double> v(n);
    for (int i = 0; i < n; i++) {
        cout << "  " << name << "[" << i + 1 << "] = ";
        cin >> v[i];
    }
    return v;
}

vector<double> forwardSub(const Matrix& L, const vector<double>& b) {
    int n = b.size();
    vector<double> y(n, 0.0);

    for (int i = 0; i < n; i++) {
        double sum = b[i];
        for (int j = 0; j < i; j++)
            sum -= L[i][j] * y[j];
        y[i] = sum / L[i][i];
    }
    return y;
}

vector<double> backwardSub(const Matrix& U, const vector<double>& y) {
    int n = y.size();
    vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; i--) {
        double sum = y[i];
        for (int j = i + 1; j < n; j++)
            sum -= U[i][j] * x[j];
        x[i] = sum / U[i][i];
    }
    return x;
}
