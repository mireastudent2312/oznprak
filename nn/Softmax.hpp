#ifndef OZNPRAK_SOFTMAX_HPP
#define OZNPRAK_SOFTMAX_HPP

#include <cmath>
#include "../Matrix.hpp"
#include "ActivationFunction.hpp"

class Softmax : public ActivationFunction {
public:
    Matrix activation(const Matrix &matrix) override;

    Matrix derivative(const Matrix &matrix) override;
};
#endif //OZNPRAK_SOFTMAX_HPP
