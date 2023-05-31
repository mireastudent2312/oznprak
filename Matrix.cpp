#include "Matrix.hpp"

#include <utility>
#include <random>

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

Matrix Matrix::random(int rows, int cols) {
    Matrix m(rows, cols);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < rows * cols; ++i) {
        m.data_[i] = dis(gen);
    }
    return m;
}

Matrix::Matrix(int rows, int cols, double value) : rows_(rows), cols_(cols), data_(rows * cols, value) {}

Matrix::Matrix(int rows, int cols, std::vector<double> values) : rows_(rows), cols_(cols), data_(std::move(values)) {
    assert(rows_ * cols_ == data_.size());
}

int Matrix::rows() const { return rows_; }

int Matrix::cols() const { return cols_; }

double &Matrix::at(int row, int col) { return data_[row * cols_ + col]; }

double Matrix::at(int row, int col) const { return data_[row * cols_ + col]; }

Matrix &Matrix::operator+=(const double &scalar) {
#pragma omp parallel for default(none) shared(scalar)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] += scalar;
    }
    return *this;
}

Matrix &Matrix::operator-=(const double &scalar) {
#pragma omp parallel for default(none) shared(scalar)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] -= scalar;
    }
    return *this;
}

Matrix &Matrix::operator*=(const double &scalar) {
#pragma omp parallel for default(none) shared(scalar)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] *= scalar;
    }
    return *this;
}

Matrix &Matrix::operator/=(const double &scalar) {
#pragma omp parallel for default(none) shared(scalar)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] /= scalar;
    }
    return *this;
}

Matrix Matrix::operator*(const double &scalar) const {
    Matrix result(*this);
#pragma omp parallel for default(none) shared(scalar, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] *= scalar;
    }
    return result;
}

Matrix Matrix::operator+(const double &scalar) const{
    Matrix result(*this);
#pragma omp parallel for default(none) shared(scalar, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] += scalar;
    }
    return result;
}


Matrix Matrix::operator-(const double &scalar) const {
    Matrix result(*this);
#pragma omp parallel for default(none) shared(scalar, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] -= scalar;
    }
    return result;
}


Matrix Matrix::operator/(const double &scalar) const{
    Matrix result(*this);
#pragma omp parallel for default(none) shared(scalar, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] /= scalar;
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &other) const {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
    Matrix result(*this);
#pragma omp parallel for default(none) shared(other, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] += other.data_[i];
    }
    return result;
}

Matrix Matrix::operator/(const Matrix &other) const {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
    Matrix result(*this);
#pragma omp parallel for default(none) shared(other, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] /= other.data_[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
    Matrix result(*this);
#pragma omp parallel for default(none) shared(other, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] -= other.data_[i];
    }
    return result;
}


void Matrix::operator+=(const Matrix &other) {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
#pragma omp parallel for default(none) shared(other)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] += other.data_[i];
    }
}

void Matrix::operator-=(const Matrix &other) {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
#pragma omp parallel for default(none) shared(other)
    for (int i = 0; i < rows_ * cols_; i++) {
        data_[i] -= other.data_[i];
    }
}

Matrix Matrix::hadamard(const Matrix &other) const {
    assert(rows_ == other.rows_ && cols_ == other.cols_);
    Matrix result(*this);
#pragma omp parallel for default(none) shared(other, result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] *= other.data_[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
    assert(cols_ == other.rows_);
    Matrix result(rows_, other.cols_);
#pragma omp parallel for collapse(3) default(none) shared(other, result)
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                result.data_[i * other.cols_ + j] += data_[i * cols_ + k] * other.data_[k * other.cols_ + j];
            }
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
    for (int i = 0; i < matrix.rows_; i++) {
        for (int j = 0; j < matrix.cols_; j++) {
            stream << matrix.data_[i * matrix.cols_ + j] << " ";
        }
        stream << std::endl;
    }
    return stream;
}

Matrix Matrix::T() const {
    Matrix output = *this;
    std::swap(output.cols_, output.rows_);
    return output;
}

double Matrix::sum() {
    double res = 0;
#pragma omp parallel for default(none) reduction(+:res)
    for (double &value: data_) {
        res += value;
    }
    return res;
}

void Matrix::resize(int rows, int cols) {
    assert(rows_ * cols_ == rows * cols);
    rows_ = rows;
    cols_ = cols;
}

Matrix Matrix::operator-() const {
    Matrix result(*this);
#pragma omp parallel for default(none) shared(result)
    for (int i = 0; i < rows_ * cols_; i++) {
        result.data_[i] = -data_[i];
    }
    return result;
}


double Matrix::max() const{
    double res = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < rows_ * cols_; i++) {
        if (data_[i] > res) {
            res = data_[i];
        }
    }
    return res;
}