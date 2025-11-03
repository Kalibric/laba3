#include "paintwidget.h"
using namespace std;
int s = 0;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    storage.changeCanvasSize(this->size().width(), this->size().height());
    setMouseTracking(true);
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
    storage.changeCanvasSize(size().width(), size().height());
    QWidget::resizeEvent(event);
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (event->button() == Qt::LeftButton)
    {
        isResizeEvent = false;
        isMoveEvent = false;
        setCursor(Qt::ArrowCursor);
        if (lastPosition == lastPositionBefore)
        {
            bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
            if (!isSelectEvent)
            {
                if (storage.isExistsSelectedToCoord(x, y))
                {
                    if (ctrlPressed)
                        storage.unSelectShapeToCoord(x, y);
                    else
                        storage.unselectAll();
                }
                else
                {
                    storage.unselectAll();
                    Shape *shape = new Circle(event->pos().x(), event->pos().y());
                    storage.add(shape);
                }
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
        if (storage.isExistsShapeToCoord(x, y) && !storage.isExistsSelectedToCoord(x, y))
        {
            if (!ctrlPressed)
                storage.unselectAll();
            isSelectEvent = storage.selectShapeToCoord(x, y);
        }
        // if (ctrlPressed)
        // {
        //     if (storage.isExistsShapeToCoors(x, y))
        //     {
        //         if (!storage.isExistsSelectedToCoors(x, y))
        //             isSelectEvent = storage.selectShapeToCoord(x, y);
        //     }
        // }
        // else
        // {
        //     if (storage.isExistsShapeToCoors(x, y))
        //     {
        //         if (!storage.isExistsSelectedToCoors(x, y))
        //         {
        //             storage.unselectAll();
        //             isSelectEvent = storage.selectShapeToCoord(x, y);
        //         }
        //     }
        // }


        lastPositionBefore = event->pos();
        lastPosition = event->pos();
        update();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (storage.isExistsSelectedShapes())
    {
        bool isResizeArea = storage.isResizeAreaShapeSelectedToCoord(event->pos().x(), event->pos().y());
        if (!isResizeEvent && !isMoveEvent)
        {
            if (isResizeArea)
                setCursor(Qt::SizeFDiagCursor);
            else
                setCursor(Qt::ArrowCursor);
        }
        if (event->buttons() & Qt::LeftButton)
        {
            int dx = event->pos().x() - lastPosition.x();
            int dy = event->pos().y() - lastPosition.y();
            if (isResizeArea || isResizeEvent)
            {
                if (!isResizeEvent)
                    setCursor(Qt::SizeFDiagCursor);
                isResizeEvent = true;
                storage.resizeSelectedShapesRelative((dx + dy) / 2);
            }
            else
            {
                if (!isMoveEvent)
                    setCursor(Qt::ClosedHandCursor);
                isMoveEvent = true;
                storage.moveSelectedShapesRelative(dx, dy);
            }
            lastPosition = event->pos();
        }
        update();
    }

}

void PaintWidget::keyPressEvent(QKeyEvent *event)
{
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;
    //bool shiftPressed
    if (event->key() == Qt::Key_Delete)
    {
        storage.removeSelectedShapes();
        update();
    }
    else if (event->key() == Qt::Key_A && ctrlPressed)
    {
        storage.selectAll();
        update();
    }
    else if (event->key() == Qt::Key_Equal)
    {
        storage.resizeSelectedShapesRelative(5);
        update();
    }
    else if (event->key() == Qt::Key_Minus)
    {
        storage.resizeSelectedShapesRelative(-5);
        update();
    }
}
