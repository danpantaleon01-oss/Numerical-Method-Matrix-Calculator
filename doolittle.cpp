#include "doolittle.h"
#include <iostream>
#include <cmath>

using namespace std;

void doolittleMethod(int n) {
        cout << "\nDOOLITTLE METHOD\n";
        cout << "------------------------------------------\n";
    // ── Step 1: Get inputs ──────────────────
    Matrix A = inputMatrix(n, n, "A");
    vector<double> b = inputVector(n, "b");

    // ── Step 2: Create empty L and U ────────
    Matrix L(n, vector<double>(n, 0.0));
    Matrix U(n, vector<double>(n, 0.0));

    // L has 1s on diagonal (Doolittle's rule)
    for (int i = 0; i < n; i++)
        L[i][i] = 1.0;

    // ── Step 3: Compute U and L ─────────────
    for (int i = 0; i < n; i++) {

        // Compute row i of U
        for (int k = i; k < n; k++) {
            double sum = A[i][k];
            for (int j = 0; j < i; j++)
                sum -= L[i][j] * U[j][k];
            U[i][k] = sum;
        }

        // Check for zero pivot
        if (fabs(U[i][i]) < 1e-12) {
            cout << "\n[ERROR] Zero pivot at row " << i + 1 << ".\n";
            cout << "Cannot proceed with Doolittle.\n";
            return;
        }

        // Compute column i of L (below diagonal)
        for (int k = i + 1; k < n; k++) {
            double sum = A[k][i];
            for (int j = 0; j < i; j++)
                sum -= L[k][j] * U[j][i];
            L[k][i] = sum / U[i][i];
        }
    }

    // ── Step 4: Show decomposed matrices ────
    printMatrix(L, "L  (Lower Triangular, 1s on diagonal)");
    printMatrix(U, "U  (Upper Triangular)");

    // ── Step 5: Solve L*y = b ───────────────
    vector<double> y = forwardSub(L, b);
    printVector(y, "Intermediate y  (from L * y = b)");

    // ── Step 6: Solve U*x = y ───────────────
    vector<double> x = backwardSub(U, y);
    printVector(x, "Solution x  (from U * x = y)");
}
