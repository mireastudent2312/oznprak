#include <QTimer>
#include "DrawingArea.hpp"

DrawingArea::DrawingArea(QWidget *parent) :
        QGraphicsView(parent) {
    scene = new DrawingScene(); // Init graphics scene
    setScene(scene); // Set graphics scene
    timer = new QTimer(); // Init Timer
    connect(timer, &QTimer::timeout, this, &DrawingArea::slotTimer);
    timer->start(100); // Run Timer
}

DrawingArea::~DrawingArea() = default;

void DrawingArea::slotTimer() {
    /* Recalculate the size of the graphic scenes, depending on the size of the window*/
    timer->stop();
    scene->setSceneRect(0, 0, width() - 20, height() - 20);
}

void DrawingArea::resizeEvent(QResizeEvent *event) {
    timer->start(100);
    QGraphicsView::resizeEvent(event);
}

QImage DrawingArea::getImage() {
    QPixmap pixmap(scene->sceneRect().size().toSize());
    QPainter painter(&pixmap);
    scene->render(&painter);
    return pixmap.toImage();
}

void DrawingArea::clear() {
    scene->clear();
}
