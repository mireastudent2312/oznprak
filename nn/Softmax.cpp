#include "Softmax.hpp"

Matrix Softmax::activation(const Matrix &matrix) {
    assert(matrix.cols() == 1);

    auto result = (matrix-matrix.max()).apply(exp);

    return result/result.sum();
}

Matrix Softmax::derivative(const Matrix &matrix) {
    auto softmax = activation(matrix);
    return softmax.hadamard(softmax.apply([](double &x){return 1-x;}));
}
