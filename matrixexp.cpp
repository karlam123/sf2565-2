#include "matrixexp.hpp"
#include "myexp.hpp"
Matrix identity(const int m);
int degTaylor(const double tol);
double getTol(const double norm, const double tol);
Matrix matrixexp(const Matrix &mat, const  double tol) {

    const int m = mat.length();

    Matrix mat_exp = identity(m);
    Matrix term = mat_exp;
    const Matrix zero = Matrix(m);

// ************** SCALING ************
    double mat_norm = mat.norm(zero);
    double b = 1.0;
    int pow = 0;
    while (mat_norm/b > 0.5) {b *= 2.0; pow++;}
    Matrix B = mat/b;
// ************************************

// ********** TAYLOR EXPANSION ********
    double B_norm = B.norm(zero);
    double B_term_norm = B_norm;
    int deg = degTaylor(getTol(mat_norm, tol));
    for (int n=0; n < deg; n++) {
        term *= B/(n+1);
        mat_exp += term;
    }
// ************************************

// ************ SQUARING **************
    for (int i=0; i < pow; ++i) {
        mat_exp *= mat_exp;
    }
// ************************************
    return mat_exp;
}

double getTol(const double norm, const double oldTol) {
    double eps = oldTol;
    while (eps*norm*myexp((1+eps)*norm, oldTol) > oldTol) { eps /=2;}
    return eps;
}
// Determine the degree of Taylor polynomial
int degTaylor(const double tol) {
    int k = 0;
    double c = 8.0;
    while (c/(k+1) > tol) {c /= 2.0; k++;}
    return k;
}

// Identity matrix
Matrix identity(const int m) {
    Matrix id = Matrix(m);
    for (int i = 0; i < m; ++i) {
        id.change(i,i,1);
    }
    return id;
}
