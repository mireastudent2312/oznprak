#include <fstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

#include <QImage>
#include <thread>
#include <QLabel>
#include "Logic.hpp"
#include "nn/Relu.hpp"
#include "nn/Softmax.hpp"
#include "omp.h"
#include "ui/Window.hpp"

Logic::Logic() {
    auto first = std::make_unique<Layer>(100, std::make_unique<Relu>());
    first->configure(28 * 28);
    neuralNetwork.addLayer(std::move(first));
    neuralNetwork.addLayer(std::make_unique<Layer>(10, std::make_unique<Softmax>()));

    trainImages = readImages("mnist/train-images.idx3-ubyte");
    testImages = readImages("mnist/t10k-images.idx3-ubyte");
    trainLabels = readLabels("mnist/train-labels.idx1-ubyte");
    testLabels = readLabels("mnist/t10k-labels.idx1-ubyte");
}

void Logic::trainNetwork(int epochs, double learningRate, Window *window, int numThreads) {
    std::thread([this, learningRate, epochs, window, numThreads](){
        omp_set_num_threads(numThreads);
        neuralNetwork.train(trainImages, trainLabels, learningRate, epochs, testImages, testLabels);
        emit window->_trainingFinished();
    }).detach();
}

std::vector<double> Logic::predictNetwork(QImage image) {
    image = image.convertToFormat(QImage::Format::Format_Grayscale8).scaled(28, 28, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    auto matrix = Matrix(28 * 28, 1, {image.bits(), image.bits() + image.sizeInBytes()}) * (1.0 / 255.0);
    return (neuralNetwork.predict(matrix).data_);

}

std::vector<Matrix> Logic::readImages(const std::string &path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
        throw std::invalid_argument("Wrong path: " + path);

    int magic;
    int n;
    int rows;
    int cols;

    file.read(reinterpret_cast<char *>(&magic), sizeof(magic));
    file.read(reinterpret_cast<char *>(&n), sizeof(n));
    file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
    file.read(reinterpret_cast<char *>(&cols), sizeof(cols));

    magic = ntohl(magic);
    n = ntohl(n);
    rows = ntohl(rows);
    cols = ntohl(cols);

    std::vector<Matrix> images(n);

    for (int i = 0; i < n; i++) {
        std::vector<double> data(rows * cols);
        for (int j = 0; j < rows * cols; j++) {
            unsigned char x;
            file.read(reinterpret_cast<char *>(&x), sizeof(x));
            data[j] = ((double) x) / 255.0;
        }
        images[i] = (Matrix(rows * cols, 1, data));
    }

    return images;
}

std::vector<Matrix> Logic::readLabels(const std::string &path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
        throw std::invalid_argument("Wrong path: " + path);

    int magic;
    int n;

    file.read(reinterpret_cast<char *>(&magic), sizeof(magic));
    file.read(reinterpret_cast<char *>(&n), sizeof(n));

    magic = ntohl(magic);
    n = ntohl(n);

    std::vector<Matrix> labels(n, Matrix(10, 1, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));

    for (int i = 0; i < n; i++) {
        unsigned char x;
        file.read(reinterpret_cast<char *>(&x), sizeof(x));
        labels[i].at(x, 0) = 1.0;
    }

    return labels;
}

std::string Logic::testNetwork() {
    int correct = neuralNetwork.test(testImages, testLabels);
    return std::to_string(correct) + "/" + std::to_string(testImages.size());
}

