#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "Window.hpp"
#include "DrawingArea.hpp"
#include <omp.h>

Window::Window(QWidget *parent) : QWidget(parent), logic(std::make_unique<Logic>()) {
    setWindowTitle("Digits Neural Network");

    drawingArea = new DrawingArea(this);
    drawingArea->setFixedSize(280, 280);

    // Left Pane
    leftPane = new QWidget(this);
    leftPaneLayout = new QVBoxLayout(this);
    leftPane->setLayout(leftPaneLayout);
    leftPane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    threadsLabel = new QLabel("Threads:", this);
    threadsSpinBox = new QSpinBox(this);
    threadsSpinBox->setMinimum(1);
    threadsSpinBox->setMaximum(omp_get_max_threads());
    threadsSpinBox->setValue(omp_get_max_threads());

    epochsLabel = new QLabel("Epochs:", this);
    epochsSpinBox = new QSpinBox(this);
    epochsSpinBox->setMinimum(1);
    epochsSpinBox->setMaximum(std::numeric_limits<int>::max());

    learningRateLabel = new QLabel("Learning rate:", this);
    learningRateSpinBox = new QDoubleSpinBox(this);
    learningRateSpinBox->setSingleStep(0.0001);
    learningRateSpinBox->setDecimals(10);
    learningRateSpinBox->setValue(0.001);

    trainButton = new QPushButton("Train", this);
    connect(trainButton, &QPushButton::clicked, this, &Window::trainButtonClicked);

    leftPane->layout()->addWidget(threadsLabel);
    leftPane->layout()->addWidget(threadsSpinBox);
    leftPane->layout()->addWidget(epochsLabel);
    leftPane->layout()->addWidget(epochsSpinBox);
    leftPane->layout()->addWidget(learningRateLabel);
    leftPane->layout()->addWidget(learningRateSpinBox);
    leftPane->layout()->addWidget(trainButton);

    // Right Pane
    rightPane = new QWidget(this);
    rightPaneLayout = new QVBoxLayout(this);
    rightPane->setLayout(rightPaneLayout);
    rightPane->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, this, &Window::clearButtonClicked);

    predictButton = new QPushButton("Predict");
    connect(predictButton, &QPushButton::clicked, this, &Window::predictButtonClicked);

    rightPane->layout()->addWidget(drawingArea);
    rightPane->layout()->addWidget(clearButton);
    rightPane->layout()->addWidget(predictButton);

    // Layout
    layout = new QHBoxLayout(this);
    layout->addWidget(leftPane);
    layout->addWidget(rightPane);
    setLayout(layout);

    connect(this, &Window::_trainingFinished, this, &Window::trainingFinished);
}

template<typename T>
int maxIndex(std::vector<T> v);

void Window::clearButtonClicked() {
    drawingArea->clear();
}

void Window::predictButtonClicked() {
    std::string text;
    auto predicted = logic->predictNetwork(drawingArea->getImage());
    for (int i = 0; i < 10; i++) {
        text += std::to_string(i) + ": " + std::to_string(int(predicted[i] * 100)) + "%\n";
    }
    QMessageBox::information(this, "Result", text.c_str());
}

Window::~Window() = default;

void Window::trainButtonClicked() {
    trainButton->setEnabled(false);

    trainingStart = std::chrono::high_resolution_clock ::now();
    logic->trainNetwork(epochsSpinBox->value(), learningRateSpinBox->value(), this, threadsSpinBox->value());
}

void Window::trainingFinished() {
    auto end = std::chrono::high_resolution_clock ::now();
    QMessageBox::information(nullptr, "Train completed", QString(("Time elapsed: " + std::to_string(
            std::chrono::duration_cast<std::chrono::seconds>(end - trainingStart).count())+"(Number of correct tests: "+logic->testNetwork()+")").c_str()));
    trainButton->setEnabled(true);
}