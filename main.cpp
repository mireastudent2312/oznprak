#include <iostream>
#include "Matrix.hpp"
#include "nn/Layer.hpp"
#include "nn/NeuralNetwork.hpp"
#include "ui/Window.hpp"
#include <qt6/QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto window = new Window;
    window->show();

    return app.exec();
}