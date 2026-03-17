#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <string>

using namespace std;

typedef vector<vector<double>> Matrix;

// label
void printMatrix(const Matrix& A, const string& label);

// Prints a vector  to the screen
void printVector(const vector<double>& v, const string& label);

// Asks the user to type in all values of a matrix
Matrix inputMatrix(int rows, int cols, const string& name);

// Asks the user to type in all values of a vector
vector<double> inputVector(int n, const string& name);

vector<double> forwardSub(const Matrix& L, const vector<double>& b);

vector<double> backwardSub(const Matrix& U, const vector<double>& y);

#endif
