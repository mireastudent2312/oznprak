#ifndef OZNPRAK_DRAWINGSCENE_HPP
#define OZNPRAK_DRAWINGSCENE_HPP

#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class DrawingScene : public QGraphicsScene {
Q_OBJECT

public:
    explicit DrawingScene(QObject *parent = nullptr);

    ~DrawingScene() override;

private:
    QPointF previousPoint;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //OZNPRAK_DRAWINGSCENE_HPP
