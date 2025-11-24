#include "shape.h"
const QString ShapeType::ShapeTypes::CIRCLE = "Circle";
const QString ShapeType::ShapeTypes::SQUARE = "Square";
const QString ShapeType::ShapeTypes::TRIANGLE = "Triangle";

Shape::Shape()
{

}

Shape::Shape(Shape &iShape)
{
    x = iShape.x;
    y = iShape.y;
    canvasSizeX = iShape.canvasSizeX;
    canvasSizeY = iShape.canvasSizeY;
    selected = iShape.selected;
    color = iShape.color;
}

void Shape::changeCanvasSize(int iX, int iY)
{
    canvasSizeX = iX;
    canvasSizeY = iY;
    moveRelative(0, 0);
}

void Shape::select()
{
    selected = true;
}

void Shape::unSelect()
{
    selected = false;
}

bool Shape::isSelect()
{
    return selected;
}

bool Shape::validateCoord(int iX, int iY)
{
    return (iX > 0) && (iX < canvasSizeX) && (iY > 0) && (iY < canvasSizeY);
}

GroupShape::~GroupShape()
{
    for (auto shape : storage)
    {
        delete shape;
    }
}

bool GroupShape::isContaints(int iX, int iY)
{
    for (auto shape : storage)
        if (shape->isContaints(iX, iY))
            return true;

    return false;
}

void GroupShape::draw(QPainter *painter)
{
    for (auto shape : storage)
        shape->draw(painter);
}

void GroupShape::changeCanvasSize(int iX, int iY)
{
    for (auto shape : storage)
        shape->changeCanvasSize(iX, iY);
}

void GroupShape::relativeResize(int iSize)
{
    for (auto shape : storage)
        shape->relativeResize(iSize);
}

bool GroupShape::isResizeArea(int iX, int iY)
{
    for (auto shape : storage)
        if (shape->isResizeArea(iX, iY))
            return true;
    return false;
}

bool GroupShape::validateCoord(int iX, int iY)
{
    for (auto shape : storage)
        if (shape->validateCoord(iX, iY))
            return true;
    return false;
}

void GroupShape::changeColor(QColor color)
{
    for (auto shape : storage)
        shape->changeColor(color);
}

void GroupShape::select()
{
    for (auto shape : storage)
        shape->select();
}

void GroupShape::unSelect()
{
    for (auto shape : storage)
        shape->unSelect();
}

bool GroupShape::isSelect()
{
    for (auto shape : storage)
        if (shape->isSelect())
            return true;
    return false;
}

void GroupShape::moveRelative(int iX, int iY)
{
    for (auto shape : storage)
        shape->moveRelative(iX, iY);
}

void GroupShape::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<GroupStorage>" << "\n";
    for (auto shape : storage)
        shape->saveInFile(out, level + 1);
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "</GroupStorage>" << "\n";
}

void GroupShape::add(Shape* shape)
{
    storage.push_back(shape);
}

vector<Shape*> GroupShape::unGrouping()
{
    vector<Shape*> result;
    for (auto shape : storage)
        result.push_back(shape);
    storage.clear();
    return result;
}

void Shape::moveRelative(int iX, int iY)
{
    bool validate = validateCoord(x + iX, y + iY);
    if (validate)
    {
        x += iX;
        y += iY;
    }
}
void Shape::changeColor(QColor iColor)
{
    color = iColor;
}

Circle::Circle()
{

}

Circle::Circle(Circle &iCircle) : Shape(iCircle)
{
    radius = iCircle.radius;
}

Circle::Circle(int iX, int iY, QColor iColor, int iRadius)
{
    x = iX;
    y = iY;
    radius = iRadius;
    color = iColor;
}

bool Circle::isContaints(int iX, int iY)
{
    int dx = iX - x;
    int dy = iY - y;
    return dx*dx+dy*dy <= radius*radius;
}

void Circle::draw(QPainter *painter)
{
    painter->setPen(selected ? QPen(Qt::white, 2) : QPen(Qt::NoPen));
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
    bool success = true;
    if ((iX + radius) > canvasSizeX)
    {
        x = canvasSizeX - radius;
        success = false;
    }
    else if ((iX - radius) < 0)
    {
        x = radius;
        success = false;
    }

    if ((iY + radius) > canvasSizeY)
    {
        y = canvasSizeY - radius;
        success = false;
    }
    else if ((iY - radius) < 0)
    {
        y = radius;
        success = false;
    }
    return success;
}

void Circle::relativeResize(int iSize)
{
    if (radius + iSize < 5)
        radius = 5;
    else if (radius + iSize > 150)
        radius = 150;
    else
        radius += iSize;
    validateCoord(x, y);
}

void Circle::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<Circle>" << "radius:" << radius << ", x:" << x << ", y:" << y << ", color:" << color.name() << "</Circle>" << "\n";
}

void Circle::load(QString &text)
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

Square::Square()
{

}

Square::Square(Square &iSquare) : Shape(iSquare)
{
    lenght = iSquare.lenght;
}

Square::Square(int iX, int iY, QColor iColor, int iLength)
{
    x = iX;
    y = iY;
    lenght = iLength;
    color = iColor;
}

bool Square::isContaints(int iX, int iY)
{
    return (iX >= x - lenght && iX <= x + lenght &&
            iY >= y - lenght && iY <= y + lenght);
}

void Square::draw(QPainter *painter)
{
    painter->setPen(selected ? QPen(Qt::white, 2, Qt::DashLine) : QPen(Qt::NoPen));
    painter->setBrush(color);
    painter->drawRect(x-lenght, y-lenght, lenght*2, lenght*2);
    if (selected)
    {
        painter->setBrush(Qt::gray);
        painter->setPen(QPen(Qt::white, 1));
        painter->drawRect(x+lenght-10, y+lenght-10, 10, 10);
    }
}

void Square::relativeResize(int iSize)
{
    if (lenght + iSize < 5)
        lenght = 5;
    else if (lenght + iSize > 150)
        lenght = 150;
    else
        lenght += iSize;
    validateCoord(x, y);
}

bool Square::validateCoord(int iX, int iY)
{
    bool success = true;
    if ((iX + lenght) > canvasSizeX)
    {
        x = canvasSizeX - lenght;
        success = false;
    }
    else if ((iX - lenght) < 0)
    {
        x = lenght;
        success = false;
    }

    if ((iY + lenght) > canvasSizeY)
    {
        y = canvasSizeY - lenght;
        success = false;
    }
    else if ((iY - lenght) < 0)
    {
        y = lenght;
        success = false;
    }
    return success;
}

bool Square::isResizeArea(int iX, int iY)
{
    return iX >= x + lenght - 10 && iX <= x + lenght &&
           iY >= y + lenght - 10 && iY <= y + lenght;
}

void Square::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<Square>" << "lenght:" << lenght << ", x:" << x << ", y:" << y << ", color:" << color.name() << "</Square>" << "\n";
}

void Square::load(QString &text)
{
    QRegularExpression lenghtExp("lenght:\\s*(\\d+)");
    QRegularExpression xExp("x:\\s*(\\d+)");
    QRegularExpression yExp("y:\\s*(\\d+)");
    QRegularExpression colorExp("color:\\s*(#[0-9A-Fa-f]{6})");

    QRegularExpressionMatch lenghtMatch = lenghtExp.match(text);
    QRegularExpressionMatch xMatch = xExp.match(text);
    QRegularExpressionMatch yMatch = yExp.match(text);
    QRegularExpressionMatch colorMatch = colorExp.match(text);

    if (lenghtMatch.hasMatch())
        lenght = lenghtMatch.captured(1).toInt();
    if (xMatch.hasMatch())
        x = xMatch.captured(1).toInt();
    if (yMatch.hasMatch())
        y = yMatch.captured(1).toInt();
    if (colorMatch.hasMatch())
        color = colorMatch.captured(1);
}

Triangle::Triangle()
{

}

Triangle::Triangle(Triangle &iTriangle) : Shape(iTriangle)
{
    h = iTriangle.h;
}

Triangle::Triangle(int iX, int iY, QColor iColor, int iH)
{
    x = iX;
    y = iY;
    h = iH;
    color = iColor;
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
    painter->setPen(selected ? QPen(Qt::white, 2, Qt::DashLine) : QPen(Qt::NoPen));
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

void Triangle::relativeResize(int iH)
{
    if (h + iH < 10)
        h = 10;
    else if (h + iH > 150)
        h = 150;
    else
        h += iH;
    validateCoord(x, y);
}

bool Triangle::validateCoord(int iX, int iY)
{
    bool success = true;
    if ((iX + h) > canvasSizeX)
    {
        x = canvasSizeX - h;
        success = false;
    }
    else if ((iX - h) < 0)
    {
        x = h;
        success = false;
    }

    if ((iY + h) > canvasSizeY)
    {
        y = canvasSizeY - h;
        success = false;
    }
    else if ((iY - h) < 0)
    {
        y = h;
        success = false;
    }
    return success;
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

void Triangle::load(QString &text)
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
