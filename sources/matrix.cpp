#include "matrix.hpp"

Matrix::Matrix(size_t m, size_t n) {
    double** data = new double*[m];
    for (size_t i = 0; i < m; i++) {
        data[i] = new double[n];
    }
}

