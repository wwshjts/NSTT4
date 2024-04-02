#include <stddef.h>
#include <vector>

class Matrix {
    double** data_;    
    size_t m_; 
    size_t n_;
public:

    Matrix(size_t m, size_t n);

    Matrix(const Matrix& other);
    Matrix(Matrix&& m);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    ~Matrix();

    explicit operator double() const;
    Matrix& operator+(const Matrix& other);
    friend Matrix& operator+(const Matrix& a, const Matrix& b);
    Matrix& operator-(const Matrix& other);
    friend Matrix& operator-(const Matrix& a, const Matrix& b);
    Matrix& operator*(const Matrix& other);
    friend Matrix& operator*(const Matrix& a, const Matrix& b);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(double a);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
};