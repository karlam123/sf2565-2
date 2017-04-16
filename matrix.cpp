#include "matrix.hpp"
#include <vector>
#include <iostream>
#include <cmath>

// Zero matrix of size mxm
Matrix::Matrix(int m) : mat_size(m){
    for (int i = 0; i < m*m; i++) {
        Matrix::matrix_array.push_back(0);
   }
}

// Build matrix of size mxm from array ar
Matrix::Matrix(int m, const double* ar, const bool isRowStyle) : mat_size(m) {
    if (isRowStyle) {
        for (int i=0; i < m*m; i++) {
            Matrix::matrix_array.push_back(ar[i]);
        }
    } else {
        for (int col=0; col < m; col++) {
            for (int row=0; row < m; row++) {
                    Matrix::matrix_array.push_back(ar[col+m*row]);
            }
        }
    }
}

Matrix::Matrix(const Matrix& m) {
    Matrix::mat_size = m.mat_size;
    Matrix::matrix_array = m.matrix_array;
}

Matrix& Matrix::operator=(const Matrix& mat) {
    if (this != &mat) {
        mat_size = mat.mat_size;
        Matrix::matrix_array = mat.matrix_array;
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& mat) {
    for (int i = 0; i < std::pow(Matrix::mat_size,2); ++i) {
        Matrix::matrix_array[i] += mat.matrix_array[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& mat) {
    Matrix tmp = Matrix(Matrix::mat_size);
    const int m = Matrix::mat_size;
    double sum = 0;
    double a=0;
    double b=0;

    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < m; ++col) {
            sum=0;
            for (int k=0; k < m; ++k) {
                a = Matrix::matrix_array[m*row+k];
                b = mat.matrix_array[m*k+col];
                sum += a*b;
            }
            tmp.matrix_array[m*row+col] = sum;
        }
    }
    Matrix::matrix_array = tmp.matrix_array;
    return *this;
}

Matrix Matrix::operator/ (double n) const {
    Matrix tmp = *this;
    for (int i = 0; i < std::pow(Matrix::mat_size, 2); ++i) {
        tmp.matrix_array[i] /= n;
    }
    return tmp;
}

double Matrix::norm(const Matrix& mat) const {
    double n = 0;
    double cor=0;
    const int m = Matrix::mat_size;
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < m; ++col) {
            cor = m*row+col;
            n += std::pow(Matrix::matrix_array[cor]-mat.matrix_array[cor],2);
        }
    }
    return std::sqrt(n);
}

void Matrix::fillMatrix(double v) {
    std::fill(Matrix::matrix_array.begin(), Matrix::matrix_array.end(), v);
}

void Matrix::printMatrix() const {
    int m = Matrix::mat_size;
    for (int row=0; row < m; row++) {
        for (int col=0; col < m; col++) {
            std::cout << Matrix::matrix_array[m*row+col] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::change(int i, int j, double v) {
    Matrix::matrix_array[Matrix::mat_size*i+j]=v;
}

int Matrix::length() const{
    return mat_size;
}
