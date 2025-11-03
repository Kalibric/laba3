#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMoveEvent>
#include "shapestorage.h"

class PaintWidget : public QWidget
{
public:
    PaintWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    ShapeStorage storage;
    QPoint lastPosition;
    QPoint lastPositionBefore;
    bool isSelectEvent = false;
    bool isResizeEvent = false;
    bool isMoveEvent = false;

};

#endif // PAINTWIDGET_H
