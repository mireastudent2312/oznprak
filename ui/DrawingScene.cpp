#include <QGraphicsScene>
#include "DrawingScene.hpp"

#define POINT_SIZE 15.0
#define COLOR Qt::white

DrawingScene::DrawingScene(QObject *parent) : QGraphicsScene(parent) {
    setBackgroundBrush(QBrush(QColor().black()));
}

DrawingScene::~DrawingScene() = default;

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // When you press the mouse button, draw the ellipse
    addEllipse(event->scenePos().x() - POINT_SIZE/2,
               event->scenePos().y() - POINT_SIZE/2,
               POINT_SIZE,
               POINT_SIZE,
               QPen(Qt::NoPen),
               QBrush(COLOR));
    // Save the coordinates of the point of pressing
    previousPoint = event->scenePos();
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // Draw the line with the previous coordinates
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(COLOR, POINT_SIZE, Qt::SolidLine, Qt::RoundCap));
    // Update on the previous coordinate data
    previousPoint = event->scenePos();
}
