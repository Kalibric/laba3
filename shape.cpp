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
    painter->setPen(selected ? QPen(Qt::white, 2) : QPen(Qt::NoPen));
    painter->setBrush(Qt::green);
    painter->drawEllipse(QPoint(x, y), radius, radius);
    if (selected)
    {
        painter->setPen(QPen(Qt::white, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(x - radius, y - radius, radius*2, radius*2);
    }
}

void Circle::select()
{
    selected = true;
}

void Circle::unSelect()
{
    selected = false;
}
