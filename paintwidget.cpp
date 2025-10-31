#include "paintwidget.h"
using namespace std;
int s = 0;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    connect(this, &MainWindow::keypressed, PaintWidget, &PaintWidget::keyPressEvent);
    //connect(this, &MainWindow::keypressed, paintWidget, &PaintWidget::keyPressEvent);
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    // Заливаем всю доступную область виджета цветом
    //painter.setBrush(backgroundRole());
    //painter.fillRect(this->rect(), backgroundRole());
    storage.drawAll(painter);
    painter->end();
    qDebug() << this->size();
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
    qDebug() << event->key();
    if (event->key() == Qt::Key_Delete)
    {
        qDebug() << "asd";
        storage.removeSelectedShapes();
    }
}
