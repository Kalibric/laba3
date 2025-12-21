#include "circle.h"

Circle::Circle()
{

}

Circle::Circle(Circle &iCircle) : Shape(iCircle)
{
    radius = iCircle.radius;
}

Circle::Circle(int iX, int iY, QColor iColor, int iRadius, int _id) : Shape(iX, iY, iColor, _id)
{
    radius = iRadius;
}

bool Circle::isContaints(int iX, int iY)
{
    int dx = iX - x;
    int dy = iY - y;
    return dx*dx+dy*dy <= radius*radius;
}

void Circle::draw(QPainter *painter)
{
    painter->setPen(selected ? QPen(Qt::white, 2) : QPen(Qt::black, 1));
    painter->setBrush(color);
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
    return iX >= x + radius - 10 && iX <= x + radius &&
           iY >= y + radius - 10 && iY <= y + radius;
}

bool Circle::validateCoord(int iX, int iY)
{
    return (iX + radius) < canvasSizeX &&
           (iX - radius) > 0 &&
           (iY + radius) < canvasSizeY &&
           (iY - radius) > 0;
}

bool Circle::validateCoordRelative(int iX, int iY)
{
    return (x + iX + radius) < canvasSizeX &&
           (x + iX - radius) > 0 &&
           (y + iY + radius) < canvasSizeY &&
           (y + iY - radius) > 0;
}

void Circle::correctionCoord()
{
    if ((x + radius) > canvasSizeX)
        x = canvasSizeX - radius;
    else if ((x - radius) < 0)
        x = radius;

    if ((y + radius) > canvasSizeY)
        y = canvasSizeY - radius;
    else if ((y - radius) < 0)
        y = radius;
}

void Circle::resizeRelative(int iSize)
{
    if (radius + iSize < 5)
        radius = 5;
    else if (radius + iSize > 150)
        radius = 150;
    else
        radius += iSize;

    if (!validateCoord(x, y))
        correctionCoord();
}

void Circle::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<Circle>" << "radius:" << radius << ", x:" << x << ", y:" << y << ", color:" << color.name() << "</Circle>" << "\n";
}

void Circle::load(QTextStream &file, QString &text)
{
    QRegularExpression radiusExp("radius:\\s*(\\d+)");
    QRegularExpression xExp("x:\\s*(\\d+)");
    QRegularExpression yExp("y:\\s*(\\d+)");
    QRegularExpression colorExp("color:\\s*(#[0-9A-Fa-f]{6})");

    QRegularExpressionMatch radiusMatch = radiusExp.match(text);
    QRegularExpressionMatch xMatch = xExp.match(text);
    QRegularExpressionMatch yMatch = yExp.match(text);
    QRegularExpressionMatch colorMatch = colorExp.match(text);
    if (radiusMatch.hasMatch())
        radius = radiusMatch.captured(1).toInt();
    if (xMatch.hasMatch())
        x = xMatch.captured(1).toInt();
    if (yMatch.hasMatch())
        y = yMatch.captured(1).toInt();
    if (colorMatch.hasMatch())
        color = colorMatch.captured(1);
}

Circle* Circle::clone()
{
    return new Circle(*this);
}

int Circle::getSize()
{
    return radius;
}

string Circle::type()
{
    return "Circle";
}

void Circle::setSize(int size)
{
    radius = size;
    if (radius + size < 5)
        radius = 5;
    else if (radius + size > 150)
        radius = 150;
    else
        radius += size;

    if (!validateCoord(x, y))
        correctionCoord();
}
