#ifndef OZNPRAK_ACTIVATIONFUNCTION_HPP
#define OZNPRAK_ACTIVATIONFUNCTION_HPP
#include "../Matrix.hpp"

class ActivationFunction {
public:
    virtual Matrix activation(const Matrix &matrix) = 0;

    virtual Matrix derivative(const Matrix &matrix) = 0;

    virtual ~ActivationFunction() = default;
};


#endif //OZNPRAK_ACTIVATIONFUNCTION_HPP
