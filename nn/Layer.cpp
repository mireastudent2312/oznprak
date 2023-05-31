#include <cmath>
#include "Layer.hpp"

Layer::Layer(int size, std::unique_ptr<ActivationFunction> activationFunction) : size(size), activationFunction(
        std::move(activationFunction)) {
    biases = Matrix::random(size, 1);
}

Matrix Layer::feedforward(const Matrix &input) {
    return activationFunction->activation(compute(input));
}

Matrix Layer::compute(const Matrix &input) {
    return (weights * input + biases);
}

void Layer::configure(int prevSize) {
    weights = Matrix::random(size, prevSize);
}

int Layer::getSize() const {
    return size;
}

void Layer::applyGradients(const Matrix &gradWeights, const Matrix &gradBiases) {
    weights -= gradWeights;
    biases -= gradBiases;
}

std::pair<Matrix, std::pair<Matrix, Matrix>> Layer::backprop(const Matrix &error, const Matrix &z, const double learningRate, const Matrix &a, bool lastLayer) {
    Matrix newError = error;
    if (lastLayer) {
        newError = error.hadamard(activationFunction->derivative(z));
    }
    return {
        weights.T() * newError,
        {
            newError * a.T() * learningRate,
            newError * learningRate
        }
    };
}