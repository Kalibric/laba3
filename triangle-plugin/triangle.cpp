#include "triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(Triangle &iTriangle) : Shape(iTriangle)
{
    h = iTriangle.h;
}

Triangle::Triangle(int iX, int iY, QColor iColor, int iH, int _id) : Shape(iX, iY, iColor, _id)
{
    h = iH;
}

bool Triangle::isContaints(int iX, int iY)
{
    QPolygon triangle;
    triangle << QPoint(x, y - h) << QPoint(x - h, y + h) << QPoint(x + h, y + h);
    return triangle.containsPoint(QPoint(iX, iY), Qt::OddEvenFill);
}

void Triangle::draw(QPainter *painter)
{
    QPolygon triangle;
    triangle << QPoint(x, y - h) << QPoint(x - h, y + h) << QPoint(x + h, y + h);
    painter->setPen(selected ? QPen(Qt::white, 2, Qt::DashLine) : QPen(Qt::black, 1));
    painter->setBrush(color);
    painter->drawPolygon(triangle);
    if (selected)
    {
        painter->setPen(QPen(Qt::white, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(x - h, y - h, h*2, h*2);
        painter->setBrush(Qt::gray);
        painter->setPen(Qt::NoPen);
        painter->drawRect(x+h-10, y+h-10, 10, 10);
    }
}

void Triangle::resizeRelative(int iH)
{
    if (h + iH < 10)
        h = 10;
    else if (h + iH > 150)
        h = 150;
    else
        h += iH;

    if (!validateCoord(x, y))
        correctionCoord();
}

bool Triangle::validateCoord(int iX, int iY)
{
    return (iX + h) < canvasSizeX &&
           (iX - h) > 0 &&
           (iY + h) < canvasSizeY &&
           (iY - h) > 0;
}

bool Triangle::validateCoordRelative(int iX, int iY)
{
    return (x + iX + h) < canvasSizeX &&
           (x + iX - h) > 0 &&
           (y + iY + h) < canvasSizeY &&
           (y + iY - h) > 0;
}

void Triangle::correctionCoord()
{
    if ((x + h) > canvasSizeX)
        x = canvasSizeX - h;
    else if ((x - h) < 0)
        x = h;

    if ((y + h) > canvasSizeY)
        y = canvasSizeY - h;
    else if ((y - h) < 0)
        y = h;
}

bool Triangle::isResizeArea(int iX, int iY)
{
    return iX >= x + h - 10 && iX <= x + h &&
           iY >= y + h - 10 && iY <= y + h;
}

void Triangle::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<Triangle>" << "h:" << h << ", x:" << x << ", y:" << y << ", color:" << color.name() << "</Triangle>" << "\n";
}

void Triangle::load(QTextStream &file, QString &text)
{
    QRegularExpression hExp("h:\\s*(\\d+)");
    QRegularExpression xExp("x:\\s*(\\d+)");
    QRegularExpression yExp("y:\\s*(\\d+)");
    QRegularExpression colorExp("color:\\s*(#[0-9A-Fa-f]{6})");

    QRegularExpressionMatch hMatch = hExp.match(text);
    QRegularExpressionMatch xMatch = xExp.match(text);
    QRegularExpressionMatch yMatch = yExp.match(text);
    QRegularExpressionMatch colorMatch = colorExp.match(text);

    if (hMatch.hasMatch())
        h = hMatch.captured(1).toInt();
    if (xMatch.hasMatch())
        x = xMatch.captured(1).toInt();
    if (yMatch.hasMatch())
        y = yMatch.captured(1).toInt();
    if (colorMatch.hasMatch())
        color = colorMatch.captured(1);
}

Triangle* Triangle::clone()
{
    return new Triangle(*this);
}

int Triangle::getSize()
{
    return h;
}

string Triangle::type()
{
    return "Triangle";
}
