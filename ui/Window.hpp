#ifndef OZNPRAK_WINDOW_HPP
#define OZNPRAK_WINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QProgressBar>
#include <QTextEdit>
#include "DrawingArea.hpp"
#include "../Logic.hpp"

class Logic;

class Window : public QWidget {
Q_OBJECT

private:
    std::unique_ptr<Logic> logic;
    std::chrono::time_point<std::chrono::high_resolution_clock> trainingStart;

    // UI elements
    DrawingArea *drawingArea;
    QLayout *layout;
    QWidget *leftPane;
    QWidget *rightPane;
    QLayout *leftPaneLayout;
    QLayout *rightPaneLayout;

    // Left Pane
    QLabel *threadsLabel;
    QSpinBox *threadsSpinBox;
    QLabel *epochsLabel;
    QSpinBox *epochsSpinBox;
    QLabel *learningRateLabel;
    QDoubleSpinBox *learningRateSpinBox;
    QPushButton *trainButton;

    // Right Pane
    QPushButton *clearButton;
    QPushButton *predictButton;
public:
    explicit Window(QWidget *parent = nullptr);

    ~Window() override;

signals:
    void _trainingFinished();

private slots:
    void predictButtonClicked();

    void clearButtonClicked();

    void trainButtonClicked();

public slots:
    void trainingFinished();
};


#endif //OZNPRAK_WINDOW_HPP
