#include "seidel.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void seidelMethod(int n) {
        cout << "\nGAUSS-SEIDEL METHOD\n";
        cout << "------------------------------------------\n";

    // ── Step 1: Get inputs ──────────────────
    Matrix A = inputMatrix(n, n, "A");
    vector<double> b = inputVector(n, "b");

    // ── Step 2: Get iteration settings ──────
    double tol;
    int maxIter;

    cout << "\nEnter tolerance (e.g. 0.0001): ";
    cin >> tol;
    cout << "Enter max iterations (e.g. 100): ";
    cin >> maxIter;

    // ── Step 3: Check for zero diagonals ────
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < 1e-12) {
            cout << "\n[ERROR] Zero on diagonal at row " << i + 1 << ".\n";
            cout << "Gauss-Seidel cannot proceed.\n";
            return;
        }
    }

    // ── Step 4: Initial guess (all zeros) ───
    vector<double> x(n, 0.0);
    vector<double> xOld(n, 0.0);

    // ── Step 5: Print table header ──────────
    cout << "\n" << setw(6) << "Iter";
    for (int i = 0; i < n; i++)
        cout << setw(14) << "x[" + to_string(i + 1) + "]";
    cout << setw(14) << "Max Error" << "\n";
    cout << string(6 + 14 * n + 14, '-') << "\n";

    bool converged = false;

    // ── Step 6: Iterate ─────────────────────
    for (int iter = 1; iter <= maxIter; iter++) {

        // Save old values before updating
        xOld = x;

        // Update each x[i] using latest values
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i)
                    sum -= A[i][j] * x[j];
            }
            x[i] = sum / A[i][i];
        }

        // Compute max error between old and new x
        double maxErr = 0.0;
        for (int i = 0; i < n; i++)
            maxErr = max(maxErr, fabs(x[i] - xOld[i]));

        // Print this iteration's row
        cout << setw(6) << iter;
        for (int i = 0; i < n; i++)
            cout << setw(14) << fixed << setprecision(6) << x[i];
        cout << setw(14) << scientific << setprecision(4) << maxErr << "\n";

        // Check if we are close enough
        if (maxErr < tol) {
            converged = true;
            cout << "\n[✓] Converged after " << iter << " iterations!\n";
            break;
        }
    }

    if (!converged)
        cout << "\n[!] Did not converge within "
             << maxIter << " iterations.\n";

    // ── Step 7: Print final answer ──────────
    printVector(x, "Final Solution x");
}
