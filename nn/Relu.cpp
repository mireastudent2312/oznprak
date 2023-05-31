#include "Relu.hpp"

Matrix Relu::activation(const Matrix &matrix) {
    return matrix.apply([](double &x) {
        return (x > 0) ? x : 0;
    });
}

Matrix Relu::derivative(const Matrix &matrix) {
    return matrix.apply([](double &x) {
        return (x > 0) ? 1 : 0;
    });
}