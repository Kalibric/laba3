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

    storage.draw(painter, ShapeType::FilterParams(ShapeType::Type::ALL));
    painter->end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    storage.changeCanvasSize(size().width(), size().height());
    QWidget::resizeEvent(event);
}

void PaintWidget::wheelEvent(QWheelEvent *event)
{
    if (storage.isExistsSelectedShapes())
    {
        storage.resizeSelectedShapesRelative(event->angleDelta().y() > 0 ? 5 : -5);
        update();
    }
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
                        storage.unSelect(x, y);
                    else
                        storage.unselectAll();
                }
                else
                {
                    storage.unselectAll();
                    Shape *shape;
                    qDebug() << selectedShape;
                    if (selectedShape == ShapeType::ShapeTypes::CIRCLE)
                        shape = new Circle(x, y, color);
                    else if (selectedShape == ShapeType::ShapeTypes::SQUARE)
                        shape = new Square(x, y, color);
                    else if (selectedShape == ShapeType::ShapeTypes::TRIANGLE)
                        shape = new Triangle(x, y, color);
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
            isSelectEvent = storage.select(x, y);
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
            if ((isResizeArea || isResizeEvent) && !isMoveEvent)
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
    if (event->key() == Qt::Key_Delete)
    {
        storage.remove();
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

void PaintWidget::changeSelectedShape(QString iSelectedShape)
{
    selectedShape = iSelectedShape;
}

void PaintWidget::changeColor(QColor iColor)
{
    color = iColor;
    storage.changeColorSelectedShapes(iColor);
}

void PaintWidget::test()
{
    // GroupStorage* st = new GroupStorage();
    // st->Grouping(storage);
    // storage.add(st);
    // update();
}
