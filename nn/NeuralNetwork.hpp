#ifndef OZNPRAK_NEURALNETWORK_HPP
#define OZNPRAK_NEURALNETWORK_HPP

#include <vector>
#include <memory>
#include <functional>
#include "Layer.hpp"

class NeuralNetwork {
private:
    std::vector<std::unique_ptr<Layer>> layers;
public:
    void addLayer(std::unique_ptr<Layer> layer);

    Matrix predict(const Matrix &input);

    static Matrix cost_derivative(const Matrix &expected, const Matrix &actual);

    void train(const std::vector<Matrix> &inputs, const std::vector<Matrix> &outputs, double learningRate, int epochs,
               const std::vector<Matrix> &testInputs = std::vector<Matrix>(),
               const std::vector<Matrix> &testOutputs = std::vector<Matrix>());

    std::vector<std::pair<Matrix, Matrix>>
    trainOne(const Matrix &input, const Matrix &output, double learningRate);

    int test(const std::vector<Matrix> &inputs, const std::vector<Matrix> &outputs);
};


#endif //OZNPRAK_NEURALNETWORK_HPP
