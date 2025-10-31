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

    storage.drawAll(painter);
    painter->end();
}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    bool ctrlPressed = event->modifiers() & Qt::ControlModifier;

    bool isSelected = storage.selectShape(event->pos().x(), event->pos().y(), ctrlPressed);
    if (!isSelected)
    {
        Shape *shape = new Circle(event->pos().x(), event->pos().y());
        storage.add(shape);
    }
    update();
}

void PaintWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        storage.removeSelectedShapes();
        update();
    }
}
