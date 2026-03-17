#include "cholesky.h"
#include <iostream>
#include <cmath>

using namespace std;

void choleskyMethod(int n) {
        cout << "\nCHOLESKY METHOD\n";
        cout << "------------------------------------------\n";
        cout << "Note: Matrix A must be SYMMETRIC\n";
        cout << "      and POSITIVE DEFINITE.\n";

    // ── Step 1: Get inputs ──────────────────
    Matrix A = inputMatrix(n, n, "A");
    vector<double> b = inputVector(n, "b");

    // ── Step 2: Create empty L matrix ───────
    Matrix L(n, vector<double>(n, 0.0));

    // ── Step 3: Compute L ───────────────────
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {

            double sum = A[i][j];

            for (int k = 0; k < j; k++)
                sum -= L[i][k] * L[j][k];

            if (i == j) {
                // Diagonal element
                if (sum <= 0) {
                    cout << "\n[ERROR] Matrix is not positive definite!\n";
                    cout << "Cannot apply Cholesky method.\n";
                    return;
                }
                L[i][j] = sqrt(sum);
            } else {
                // Below diagonal element
                L[i][j] = sum / L[j][j];
            }
        }
    }

    // ── Step 4: Build L transpose (L^T) ─────
    Matrix Lt(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Lt[i][j] = L[j][i];

    // ── Step 5: Show decomposed matrices ────
    printMatrix(L,  "L  (Lower Triangular)");
    printMatrix(Lt, "L^T (Upper Triangular)");

    // ── Step 6: Solve L*y = b ───────────────
    vector<double> y = forwardSub(L, b);
    printVector(y, "Intermediate y  (from L * y = b)");

    // ── Step 7: Solve L^T*x = y ─────────────
    vector<double> x = backwardSub(Lt, y);
    printVector(x, "Solution x  (from L^T * x = y)");
}
