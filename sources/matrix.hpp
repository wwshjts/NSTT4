#include <stddef.h>
#include <vector>
#include <utility>

class Matrix {
    size_t n_;
    double** data_;    
    void init_data();
    void cpy_data(const Matrix& other);
    void free_data();
    void check_args(size_t i, size_t j) const;

public:
    Matrix(size_t n);
    Matrix(const std::pair<size_t, size_t>& size);

    Matrix(const Matrix& other);
    Matrix(Matrix&& m);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix(const std::vector<double>& d);
    ~Matrix();

    // getters
    size_t size() const;
    double get(size_t i, size_t j) const;

    // setters
    void set(size_t i, size_t j, double value);

    // operator overloading
    //Matrix operator+(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    friend Matrix operator+(const Matrix& a, const Matrix& b);

    friend Matrix operator-(const Matrix& a, const Matrix& b);
    Matrix& operator-=(const Matrix& other);

    friend Matrix operator*(const Matrix& a, const Matrix& b);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(double a);

    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);

    explicit operator double() const;
};