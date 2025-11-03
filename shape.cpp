#include "shape.h"

Shape::Shape()
{

}

void Shape::changeCanvasSize(int iX, int iY)
{
    canvasSizeX = iX;
    canvasSizeY = iY;
    changeRelativeCoord(0, 0);
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
        painter->setBrush(Qt::gray);
        painter->setPen(Qt::NoPen);
        painter->drawRect(x+radius-10, y+radius-10, 10, 10);
    }
}

bool Circle::isResizeArea(int iX, int iY)
{
    return iX >= x + radius - 10 && iY <= x + radius &&
           iY >= y + radius - 10 && iY <= y + radius;
}

void Circle::changeRelativeCoord(int iX, int iY)
{
    if ((x + iX + radius) > canvasSizeX)
        x = canvasSizeX - radius;
    else if ((x + iX - radius) < 0)
        x = radius;
    else
        x += iX;

    if ((y + iY + radius) > canvasSizeY)
        y = canvasSizeY - radius;
    else if ((y + iY - radius) < 0)
        y = radius;
    else
        y += iY;
}

void Circle::relativeResize(int iSize)
{
    if (radius + iSize < 5)
        radius = 5;
    else if (radius + iSize > 150)
        radius = 150;
    else
        radius += iSize;
    changeRelativeCoord(0, 0);
}

void Shape::select()
{
    selected = true;
}

void Shape::unSelect()
{
    selected = false;
}

void Shape::changeRelativeCoord(int iX, int iY)
{
    qDebug() << "s";
    if ((x + iX) > 0)
        x += iX;
    if ((y + iX) > 0)
        y += iY;
}
