#ifndef OZNPRAK_LAYER_HPP
#define OZNPRAK_LAYER_HPP

#include <memory>
#include "../Matrix.hpp"
#include "ActivationFunction.hpp"
#include "Sigmoid.hpp"

class Layer {
private:
    int size;
    Matrix weights;
    Matrix biases;
public:
    [[nodiscard]] int getSize() const;

    std::unique_ptr<ActivationFunction> activationFunction;

    explicit Layer(int size, std::unique_ptr<ActivationFunction> activationFunction = std::make_unique<Sigmoid>());

    void configure(int prevSize);

    void applyGradients(const Matrix &gradWeights, const Matrix &gradBiases);

    Matrix compute(const Matrix &);

    Matrix feedforward(const Matrix &);

    std::pair<Matrix, std::pair<Matrix, Matrix>> backprop(const Matrix &error, const Matrix &z, const double learningRate, const Matrix &a, bool lastLayer = false);
    friend class NeuralNetwork;
};


#endif //OZNPRAK_LAYER_HPP
