#ifndef OZNPRAK_MATRIX_HPP
#define OZNPRAK_MATRIX_HPP

#include <iostream>
#include <vector>
#include <cassert>

class Matrix {
private:
    int rows_;
    int cols_;

public:
    std::vector<double> data_;

    Matrix() = default;

    Matrix(int rows, int cols);

    Matrix(int rows, int cols, double value);

    Matrix(int rows, int cols, std::vector<double> values);

    Matrix(const Matrix &other) = default;

    Matrix &operator=(const Matrix &other) = default;

    [[nodiscard]] int rows() const;

    [[nodiscard]] int cols() const;

    [[nodiscard]] double &at(int row, int col);

    [[nodiscard]] double at(int row, int col) const;

    void set(int row, int col, double value) { data_[row * cols_ + col] = value; }

    Matrix &operator+=(const double &scalar);

    Matrix &operator-=(const double &scalar);

    Matrix &operator*=(const double &scalar);

    Matrix operator*(const double &scalar) const;

    Matrix operator+(const double &scalar) const;

    Matrix operator-(const double &scalar) const;

    Matrix operator/(const double &scalar) const;

    Matrix &operator/=(const double &scalar);

    Matrix operator+(const Matrix &other) const;

    void operator+=(const Matrix &other);

    void operator-=(const Matrix &other);

    Matrix operator-(const Matrix &other) const;

    Matrix operator/(const Matrix &other) const;

    Matrix operator-() const;

    Matrix operator*(const Matrix &other) const;

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);

    template<typename F>
    Matrix apply(F f) const {
        Matrix result(*this);
        for (auto &value: result.data_) {
            value = f(value);
        }
        return result;
    }

    [[nodiscard]] Matrix T() const;

    double sum();

    [[nodiscard]] Matrix hadamard(const Matrix &other) const;

    static Matrix random(int rows, int cols);

    void resize(int rows, int cols);

    [[nodiscard]] double max() const;
};

#endif //OZNPRAK_MATRIX_HPP
