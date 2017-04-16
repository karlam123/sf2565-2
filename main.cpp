#include <iostream>
#include <cmath>
#include "myexp.hpp"
#include "matrix.hpp"
#include "matrixexp.hpp"

using namespace std;
#include "r8mat_expm1.h"
#include "r8lib.h"
void comparing();


using std::cout;

int main()
{
    comparing();
    return 0;
}

// Calculate matrixexp using r8lib and convert to Matrix
Matrix toExpMatrix(int m, double a[]) {
    double* mexp = r8mat_expm1(m,a);
    return Matrix(m, mexp, false);
}

void comparing() {
    // Task 1 - comparsion of myexp and exp
    cout << "********** Task 1 ************" << endl;
    const double tolerance[] = {1e-2, 1e-10, 1e-13};
    const double xs[] = {-10, 2, 10};
    cout << " x    tol    |exp(x)-myexp(x)|" << endl;
    cout << "------------------------" << endl;
    for (const double tol : tolerance) {
            for (const double x : xs) {
                    cout << x << "   " << tol << "    " << fabs(exp(x)-myexp(x,tol)) << endl;
            }
    }
    cout << "******************************" << endl;

    // Task 2 - comparsion of matrixexp and Matlab's algorithm for matrix exponential
    double m1[] = {1, 2, 3, 4};
    Matrix mat1 = Matrix(2, m1, false);
    Matrix exp1 = toExpMatrix(2, m1);

    double m2[] = {-2, 7, 8, -5, 12, -13, 1, 5, 6};
    Matrix mat2 = Matrix(3, m2, false);
    Matrix exp2 = toExpMatrix(3, m2);

    double m3[] = {-49, -64, 24, 31};
    Matrix mat3 = Matrix(2, m3, false);
    Matrix exp3 = toExpMatrix(2, m3);

    double m4[] = {-5, -4, 1, 8, 11, 2, 2, 1, 7, -4, 1, 5, 1, 2, 1, 1};
    Matrix mat4 = Matrix(4, m4, false);
    Matrix exp4 = toExpMatrix(4, m4);

    Matrix mats[] = {mat1, mat2, mat3, mat4};
    Matrix exps[] = {exp1, exp2, exp3, exp4};

    cout << "********** Task 2 ************" << endl;
    cout << " A    tol    ||exp(A)-myexp(A)||" << endl;
    for (const double tol : tolerance) {
        for (int i = 0; i < 4; ++i) {
            cout << "A_" << (i+1) << "   " << tol << "    " << matrixexp(mats[i], tol).norm(exps[i]) << endl;
        }
    }
    cout << "******************************" << endl;

}

