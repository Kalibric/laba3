#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QMoveEvent>
#include <QWheelEvent>
#include "shapestorage.h"
#include <QMenu>
#include <QAction>
#include "command.h"
#include <QColorDialog>
#include <QFileDialog>
#include "shapetree.h"
#include "mainwindow.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void changeSelectedShape(QString iSelectedShape);
    void changeColor(QColor iColor);
    void groupingButtonClick();
    void select(FilterShape params);
    void unSelect(FilterShape params);
    void saveButton();
    void loadButton();

    void setGroupingEvent(QAction *newGroupingEvent);
    void resetGroupingEvent();
    void validateGroupingButton();
    void setStorage(ShapeStorage *iStorage);

signals:
    void groupingButton();
    void unGroupingButton();
    void deactivateButton();

    void groupingEventChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    ShapeStorage *storage = new ShapeStorage();
    QPoint lastPosition;
    QPoint lastPositionBefore;
    bool isSelectEvent = false;
    bool isResizeEvent = false;
    bool isMoveEvent = false;
    QString currentShapeType = "Circle";
    QColor color = Qt::green;
    QMenu* contextMenu;
    QMenu* changeShapeType;
    QAction* removeEvent;
    QAction* setColorEvent;
    QAction* menuGroupingEvent;
    QAction* menuUnGroupingEvent;
    QAction* selectAllEvent;

    QAction* circleType;
    QAction* squareType;
    QAction* triangleType;
    CommandManager manager;
    int resize = 0;



private slots:
    void removeAction();
    void setColorAction();
    void groupingAction();
    void unGroupingAction();
    void changeShapeTypeToCircle();
    void changeShapeTypeToSquare();
    void changeShapeTypeToTriangle();

    void selectAllAction();
    void selectUpdated();

};

#endif // PAINTWIDGET_H
