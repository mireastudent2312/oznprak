#include <cmath>
#include "Sigmoid.hpp"

double Sigmoid::activation_single(double x) {
    if (x >= 0.0) {
        return 1.0 / (1.0 + std::exp(-x));
    } else {
        double exp_x = std::exp(x);
        return exp_x / (1.0 + exp_x);
    }
}

Matrix Sigmoid::activation(const Matrix &matrix) {
    return matrix.apply([](double &x) {
        return activation_single(x);
    });
}

Matrix Sigmoid::derivative(const Matrix &matrix) {
    return matrix.apply([](double &x) {
        double sigmoid = activation_single(x);
        return sigmoid * (1.0 - sigmoid);
    });
}