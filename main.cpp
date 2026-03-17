#include <iostream>
#include "matrix_utils.h"
#include "cholesky.h"
#include "doolittle.h"
#include "crout.h"
#include "seidel.h"

using namespace std;

int main() {

    // ── Welcome Banner ───────────────────────
   cout << "MATRIX SOLVER - numcoding\n";
   cout << "Cholesky | Doolittle | Crout | Seidel\n";

    bool running = true;

    while (running) {

        // ── Step 1: Ask for matrix size ──────
        int rows, cols;

        cout << "Enter number of rows    : ";
        cin  >> rows;
        cout << "Enter number of columns : ";
        cin  >> cols;

        // ── Step 2: Validate square matrix ───
        if (rows != cols) {
            cout << "\n[ERROR] Matrix must be SQUARE (rows == cols).\n";
            cout << "All 4 methods require a square matrix.\n";
            cout << "Please try again.\n";
            continue;
        }

        if (rows <= 0) {
            cout << "\n[ERROR] Size must be greater than 0.\n";
            continue;
        }

        int n = rows;
        cout << "\nMatrix size accepted: " << n << " x " << n << "\n";

        // ── Step 3: Show method menu ─────────
        cout << "\nSELECT A METHOD TO SOLVE Ax=b\n";
        cout << "1. Cholesky Decomposition\n";
        cout << "2. Doolittle Decomposition\n";
        cout << "3. Crout's Decomposition\n";
        cout << "4. Gauss-Seidel Iterative Method\n";
        cout << "0. Exit Program\n";
        cout << "\n";
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        // ── Step 4: Call chosen method ───────
        switch (choice) {
            case 1:
                choleskyMethod(n);
                break;

            case 2:
                doolittleMethod(n);
                break;

            case 3:
                croutMethod(n);
                break;

            case 4:
                seidelMethod(n);
                break;

            case 0:
                cout << "\nExiting program. Goodbye!\n";
                running = false;
                break;

            default:
                cout << "\n[!] Invalid choice.\n";
                cout << "Please enter 1, 2, 3, 4 or 0.\n";
        }

        // ── Step 5: Ask to continue ──────────
        if (running) {
            cout << "\n-------------------------------------\n";
            cout << "Solve another system? (1 = Yes  0 = No): ";
            int again;
            cin >> again;
            if (again != 1) {
                cout << "\nThank you for using Matrix Solver!\n";
                running = false;
            }
        }
    }

    return 0;
}
