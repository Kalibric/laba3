#include "shape.h"
int shapeID = 0;
using namespace std;
Shape::Shape()
{
    id = shapeID++;
}

Shape::Shape(Shape &iShape)
{
    x = iShape.x;
    y = iShape.y;
    canvasSizeX = iShape.canvasSizeX;
    canvasSizeY = iShape.canvasSizeY;
    selected = iShape.selected;
    color = iShape.color;
    id = iShape.id;
}

Shape::Shape(int iX, int iY, QColor iColor, int _id) : x(iX), y(iY), color(iColor)
{
    id = _id == -1 ? shapeID++ : _id;
}

void Shape::changeCanvasSize(int iX, int iY)
{
    canvasSizeX = iX;
    canvasSizeY = iY;

    if (!validateCoord(iX, iY))
        correctionCoord();
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

bool Shape::validateCoordRelative(int iX, int iY)
{
    return ((x + iX) > 0) && ((x + iX) < canvasSizeX) && ((y + iY) > 0) && ((y + iY) < canvasSizeY);
}

void Shape::correctionCoord()
{
    if (x < 0)
        x = 0;
    else if (x > canvasSizeX)
        x = canvasSizeX;

    if (y < 0)
        y = 0;
    else if (y > canvasSizeY)
        y = canvasSizeY;
}

void Shape::moveRelative(int iX, int iY)
{
    bool validate = validateCoord(x + iX, y + iY);
    if (validate)
    {
        x += iX;
        y += iY;
        for (callback callback : onMoved)
            callback.func(iX, iY);
    }
}

string Shape::type()
{
    return "Shape";
}

void Shape::changeColor(QColor iColor)
{
    color = iColor;
}

int Shape::addOnMoved(moveCallback func)
{
    int id = callbackIdCounter++;
    onMoved.push_back({id, func});
    return id;
}

void Shape::removeOnMoved(int id)
{
    onMoved.erase(
        std::remove_if(onMoved.begin(), onMoved.end(),
                       [id](callback& e) {
                           return e.id == id;
                       }),
        onMoved.end());
}
