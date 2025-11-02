#include "paintwidget.h"
using namespace std;
int s = 0;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    storage.drawAllShapes(painter);
    painter->end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // 1. Если нажат КТРЛ и нажат на не выделенную фигуру - Добавить фигуру в список выделенных
    // 2. Если нажат КТРЛ и нажат на выделенную фигуру - Убрать фигуру в список выделенных
    // 3. Если не нажат КТРЛ и нажат на не выделенную фигуру - Выделить фигуру, убрать выделение всех остальных
    // 4. Если не нажат КТРЛ и нажат на выделенную фигуру - Убрать выделение всех фигур
    int x = event->pos().x(), y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        if (lastPosition == lastPositionBefore)
        {
            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            if (!isSelectEvent)
            {
                qDebug() << "s-1";
                Shape *shape = new Circle(event->pos().x(), event->pos().y());
                storage.add(shape);
                update();
            }
            else if (!ctrlPressed)
            {
                qDebug() << "s-2";
                storage.unSelectShapeToCoord(x, y);
                update();
            }
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    isSelectEvent = false;
    if (event->button() == Qt::LeftButton)
    {
        bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
        if (ctrlPressed)
        {
            if (storage.isExistsShapeToCoors(x, y))
            {
                qDebug() << "s-3";
                if (!storage.isExistsSelectedToCoors(x, y))
                    isSelectEvent = storage.selectShapeToCoord(x, y);
            }
        }
        else
        {
            if (storage.isExistsShapeToCoors(x, y))
            {
                if (!storage.isExistsSelectedToCoors(x, y))
                {
                    qDebug() << "s-4";
                    storage.unselectAll();
                    isSelectEvent = storage.selectShapeToCoord(x, y);
                }
            }

        }


        lastPositionBefore = event->pos();
        lastPosition = event->pos();
        update();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (storage.isExistsSelectedShapes())
    {
        storage.moveSelectedShapesRelative(event->pos().x() - lastPosition.x(), event->pos().y() - lastPosition.y());
        lastPosition = event->pos();
        update();
    }
}

void PaintWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        storage.removeSelectedShapes();
        update();
    }
}
