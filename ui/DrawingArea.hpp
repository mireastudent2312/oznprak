#ifndef OZNPRAK_DRAWINGAREA_HPP
#define OZNPRAK_DRAWINGAREA_HPP

#include <QWidget>
#include <QGraphicsView>
#include "DrawingScene.hpp"

class DrawingArea : public QGraphicsView {
Q_OBJECT

public:
    explicit DrawingArea(QWidget *parent = nullptr);

    ~DrawingArea() override;

    QImage getImage();

    void clear();

private:
    QTimer *timer;
    DrawingScene *scene;

    void resizeEvent(QResizeEvent *event) override;

private slots:
    void slotTimer();
};


#endif //OZNPRAK_DRAWINGAREA_HPP
