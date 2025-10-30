#include "paintwidget.h"
using namespace std;
int s = 0;
PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "asad" << s++;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Заливаем всю доступную область виджета цветом
    painter.setBrush(backgroundRole());
    painter.fillRect(this->rect(), backgroundRole());

    // Дополнительно можно рисовать на холсте
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(10, 10, "Hello, Qt!"); // Пример текста

}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
