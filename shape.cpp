#include "shape.h"

Shape::Shape()
{

}

Circle::Circle()
{

}

Circle::Circle(int iX, int iY, int iRadius)
{
    x = iX;
    y = iY;
    radius = iRadius;
}

bool Circle::isClicked(int iX, int iY)
{
    int dx = iX - x;
    int dy = iY - y;
    return dx*dx+dy*dy <= radius*radius;
}

void Circle::draw(QPainter *painter)
{
    qDebug() << (selected ? Qt::blue : Qt::NoPen);
    // painter->setPen(selected ? Qt::blue : Qt::NoPen);
    if (selected)
        painter->setPen(Qt::blue);
    else
        painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    painter->drawEllipse(QPoint(x, y), radius, radius);
}

void Circle::select()
{
    selected = true;
}

void Circle::unSelect()
{
    selected = false;
}
