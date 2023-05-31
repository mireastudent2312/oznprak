#ifndef OZNPRAK_LOGIC_HPP
#define OZNPRAK_LOGIC_HPP

#include "nn/NeuralNetwork.hpp"
#include "ui/Window.hpp"

class Window;

class Logic {
private:
public:
    NeuralNetwork neuralNetwork;
    std::vector<Matrix> trainImages;
    std::vector<Matrix> testImages;
    std::vector<Matrix> trainLabels;
    std::vector<Matrix> testLabels;
    static std::vector<Matrix> readImages(const std::string& path);
    static std::vector<Matrix> readLabels(const std::string& path);

public:
    Logic();

    void trainNetwork(int epochs, double learningRate, Window *window, int numThreads);

    std::string testNetwork();

    std::vector<double> predictNetwork(QImage image);
};


#endif //OZNPRAK_LOGIC_HPP
