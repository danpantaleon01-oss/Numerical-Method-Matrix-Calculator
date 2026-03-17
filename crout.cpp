#include "crout.h"
#include <iostream>
#include <cmath>

using namespace std;

void croutMethod(int n) {
        cout << "\nCROUT'S METHOD\n";
        cout << "------------------------------------------\n";

    // ── Step 1: Get inputs ──────────────────
    Matrix A = inputMatrix(n, n, "A");
    vector<double> b = inputVector(n, "b");

    // ── Step 2: Create empty L and U ────────
    Matrix L(n, vector<double>(n, 0.0));
    Matrix U(n, vector<double>(n, 0.0));

    // U has 1s on diagonal (Crout's rule)
    for (int i = 0; i < n; i++)
        U[i][i] = 1.0;

    // ── Step 3: Compute L and U ─────────────
    for (int j = 0; j < n; j++) {

        // Compute column j of L (top to bottom)
        for (int i = j; i < n; i++) {
            double sum = A[i][j];
            for (int k = 0; k < j; k++)
                sum -= L[i][k] * U[k][j];
            L[i][j] = sum;
        }

        // Check for zero pivot
        if (fabs(L[j][j]) < 1e-12) {
            cout << "\n[ERROR] Zero pivot at column " << j + 1 << ".\n";
            cout << "Cannot proceed with Crout's method.\n";
            return;
        }

        // Compute row j of U (right of diagonal)
        for (int i = j + 1; i < n; i++) {
            double sum = A[j][i];
            for (int k = 0; k < j; k++)
                sum -= L[j][k] * U[k][i];
            U[j][i] = sum / L[j][j];
        }
    }

    // ── Step 4: Show decomposed matrices ────
    printMatrix(L, "L  (Lower Triangular)");
    printMatrix(U, "U  (Upper Triangular, 1s on diagonal)");

    // ── Step 5: Solve L*y = b ───────────────
    vector<double> y = forwardSub(L, b);
    printVector(y, "Intermediate y  (from L * y = b)");

    // ── Step 6: Solve U*x = y ───────────────
    vector<double> x = backwardSub(U, y);
    printVector(x, "Solution x  (from U * x = y)");
}
