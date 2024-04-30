#include <cassert>
#include <iostream>
#include <stdexcept>
#include "matrix.hpp"

static size_t min(size_t a, size_t b) {
    return (a <= b) ? a : b;
}

void Matrix::init_data() {
    data_ = new double*[n_];
    for (size_t i = 0; i < n_; i++) {
        data_[i] = new double[n_]{};
    }
}

void Matrix::cpy_data(const Matrix &other)
{
    assert(data_ != nullptr);
    assert(n_ == other.n_);

    for (size_t i = 0; i < n_; i++) {
        for (size_t j = 0; j < n_; j++) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

void Matrix::free_data() {
    if (data_ == nullptr) {
        return;
    }
    for (size_t i = 0; i < n_; i++) {
        delete[] data_[i];
    }
    delete[] data_;
}

void Matrix::check_args(size_t i, size_t j) const {
    if ( (i >= n_) || (j >= n_) ) {
        throw std::out_of_range("Index error: indexes out of range");
    }
}

void Matrix::check_arg(size_t i) const {
    if (i >= n_) {
        throw std::out_of_range("Index error: indexes out of range");
    }
}

Matrix::Matrix(const Matrix& other) : n_{ other.n_ } { 
    init_data();
    cpy_data(other);
}

Matrix::Matrix(Matrix&& other) : n_{ other.n_} {
    data_ = other.data_;
    other.data_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    free_data();
    n_ = other.n_;
    init_data();
    cpy_data(other);
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
    free_data();
    n_ = other.n_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

Matrix::Matrix(size_t n) : n_ { n } {
    init_data();
}

Matrix::Matrix(const std::vector<double>& diag) : Matrix(diag.size()) {
    for (size_t i = 0; i < diag.size(); i++) {
        data_[i][i] = diag[i];
    } 
}

Matrix::~Matrix() {
    free_data();
}

// getters
size_t Matrix::size() const {
    return n_;
}


double Matrix::get(size_t i, size_t j) const {
    check_args(i, j);
    return data_[i][j];
}

void Matrix::set(size_t i, size_t j, double val) {
    check_args(i, j);
    data_[i][j] = val;
}

// operator overloading
Matrix& Matrix::operator+=(const Matrix& other) {
    size_t size = min(n_, other.n_);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            set(i, j, get(i, j) + other.get(i, j));
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    size_t size = min(n_, other.n_);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            set(i, j, get(i, j) * other.get(i, j));
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(double a) {
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            set(i, j, get(i, j) * a);
        }
    }
    return *this;
}

Matrix::RowGetter Matrix::operator[](size_t i) {
    if (i >= n_) {
        throw std::out_of_range("Index out of range");
    }
    return RowGetter { data_[i], n_ };
}

bool Matrix::operator==(const Matrix& other) {
    if (n_ != other.n_) {
        return false;
    }

    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < other.size(); j++) {
            if (get(i, j) != other.get(i, j)) {
                return false;
            }
        } 
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) {
    return !(*this == other);
}

Matrix::operator double() const
{
    long double sum = 0;

    for (size_t i = 0; i < n_; i++) {
        for (size_t j = 0; j < n_; j++) {
            sum += get(i, j);
        }
    }
    return sum;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    size_t size = min(n_, other.n_);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            set(i, j, get(i, j) - other.get(i, j));
        }
    }
    return *this;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
    size_t size = min(a.n_, b.n_);
    Matrix m { size };
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            m.set(i, j, a.get(i, j) + b.get(i, j));
        }
    }
    return m;   
}

Matrix operator-(const Matrix& a, const Matrix& b) {
    size_t size = min(a.size(), b.size());
    Matrix m { size };
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            m.set(i, j, a.get(i, j) - b.get(i, j));
        }
    }
    return m;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
    size_t size = min(a.size(), b.size());
    Matrix m { size };
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            m.set(i, j, a.get(i, j) * b.get(i, j));
        }
    }
    return m;
}


Matrix::RowGetter::RowGetter(double* data, size_t size) : row_ { data }, size_ { size } {}

double& Matrix::RowGetter::operator[](size_t j) {
    if (j >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return row_[j];
}
