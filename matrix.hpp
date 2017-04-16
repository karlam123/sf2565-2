#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix {
    private:
        std::vector<double> matrix_array;  // Store matrix as vector
        int mat_size;
    public:
        Matrix(int m);
        Matrix(int m, const double* ar, const bool isRowStyle=true);
        Matrix(const Matrix& m);
        Matrix& operator=(const Matrix&);
        Matrix& operator+=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix operator/ (double) const;
        double norm(const Matrix&) const;
        void printMatrix() const;
        void fillMatrix(double v);
        void change(int i, int j, double v);
        int length() const;

};

#endif
