#include <algorithm>
#include "NeuralNetwork.hpp"

void NeuralNetwork::addLayer(std::unique_ptr<Layer> layer) {
    if (!layers.empty())
        layer->configure(layers.back()->getSize());
    layers.push_back(std::move(layer));
}

Matrix NeuralNetwork::predict(const Matrix &input) {
    Matrix output = input;
    for (const auto &layer: layers) {
        output = layer->feedforward(output);
    }
    return output;
}

// square mean error
Matrix NeuralNetwork::cost_derivative(const Matrix &expected, const Matrix &actual) {
    return actual - expected;
}

void NeuralNetwork::train(const std::vector<Matrix> &inputs, const std::vector<Matrix> &outputs, double learningRate,
                          int epochs,
                          const std::vector<Matrix> &testInputs, const std::vector<Matrix> &testOutputs) {
    assert(inputs.size() == outputs.size());
    assert(testInputs.size() == testOutputs.size());

    for (int epoch = 0; epoch < epochs; ++epoch) {
#pragma omp parallel for default(none) shared(inputs, outputs, learningRate)
        for (size_t i = 0; i < inputs.size(); i++) {
            auto grads = trainOne(inputs[i], outputs[i], learningRate);
#pragma omp critical
            for (size_t k = 0; k < layers.size(); k++) {
                layers[k]->applyGradients(grads[k].first, grads[k].second);
            }
        }
    }
}

std::vector<std::pair<Matrix, Matrix>>
NeuralNetwork::trainOne(const Matrix &input, const Matrix &output, double learningRate) {
    std::vector<Matrix> gradWeights(layers.size());
    std::vector<Matrix> gradBiases(layers.size());


    std::vector<Matrix> zs{};
    std::vector<Matrix> as{input};

    // forward propagation
    for (auto &layer: layers) {
        zs.push_back(layer->compute(as.back()));
        as.push_back(layer->activationFunction->activation(zs.back()));
    }

    Matrix error = cost_derivative(output, as.back());

    std::vector<std::pair<Matrix, Matrix>> grads(layers.size());
    for (int i = layers.size() - 1; i >= 0; i--) {
        auto [error_, grad_] = layers[i]->backprop(error, zs[i], learningRate, as[i], i != layers.size() - 1);
        error = error_;
        grads[i] = grad_;
    }

    return grads;
}

template<typename T>
int maxIndex(std::vector<T> v) {
    int maxIndex = 0;
    double maxValue = v[0];

    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > maxValue) {
            maxValue = v[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

int NeuralNetwork::test(const std::vector<Matrix> &inputs, const std::vector<Matrix> &outputs) {
    int correct = 0;
    if (!inputs.empty()) {
#pragma omp parallel for default(none) reduction(+:correct) shared(inputs, outputs)
        for (int i = 0; i < inputs.size(); i++) {
            if (maxIndex(predict(inputs[i]).data_) == maxIndex(outputs[i].data_)) {
                ++correct;
            }
        }
    }
    return correct;
}
