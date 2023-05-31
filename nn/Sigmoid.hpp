#ifndef OZNPRAK_SIGMOID_HPP
#define OZNPRAK_SIGMOID_HPP

#include "ActivationFunction.hpp"
#include "../Matrix.hpp"

class Sigmoid : public ActivationFunction {
private:
    static double activation_single(double x);

public:
    Matrix activation(const Matrix &matrix) override;

    Matrix derivative(const Matrix &matrix) override;
};


#endif //OZNPRAK_SIGMOID_HPP
