#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include "shapestorage.h"
#include "mainwindow.h"

class PaintWidget : public QWidget
{
public:
    PaintWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    ShapeStorage storage;


};

#endif // PAINTWIDGET_H
