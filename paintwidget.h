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

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void changeSelectedShape(QString iSelectedShape);
    void changeColor(QColor iColor);
    void groupingButtonClick();
    void select(ShapeType::FilterParams params);
    void unSelect(ShapeType::FilterParams params);
    void saveButton();
    void loadButton();

    void setGroupingEvent(QAction *newGroupingEvent);
    void resetGroupingEvent();

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
    ShapeStorage storage;
    QPoint lastPosition;
    QPoint lastPositionBefore;
    bool isSelectEvent = false;
    bool isResizeEvent = false;
    bool isMoveEvent = false;
    QColor color = Qt::green;
    QMenu* contextMenu;
    QAction* removeEvent;
    QAction* setColorEvent;
    QAction* menuGroupingEvent;
    QAction* menuUnGroupingEvent;
    QAction* selectAllEvent;

    // Q_PROPERTY(QAction *menuGroupingEvent READ menuGroupingEvent WRITE setGroupingEvent RESET resetGroupingEvent NOTIFY groupingEventChanged FINAL)

private slots:
    void removeAction();
    void setColorAction();
    void groupingAction();
    void unGroupingAction();

    void selectAllAction();

};

#endif // PAINTWIDGET_H
