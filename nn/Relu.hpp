#ifndef OZNPRAK_RELU_HPP
#define OZNPRAK_RELU_HPP

#include "ActivationFunction.hpp"
#include "../Matrix.hpp"

class Relu : public ActivationFunction {
public:
    Matrix activation(const Matrix &matrix) override;

    Matrix derivative(const Matrix &matrix) override;

    ~Relu() override = default;
};

#endif //OZNPRAK_RELU_HPP
