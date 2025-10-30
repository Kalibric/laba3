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

    // �������� ��� ��������� ������� ������� ������
    painter.setBrush(backgroundRole());
    painter.fillRect(this->rect(), backgroundRole());

    // ������������� ����� �������� �� ������
    painter.setPen(QPen(Qt::black, 2));
    painter.drawText(10, 10, "Hello, Qt!"); // ������ ������

}

void PaintWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
