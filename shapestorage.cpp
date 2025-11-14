#include "shapestorage.h"
using namespace std;
ShapeStorage::ShapeStorage()
{

}

void ShapeStorage::add(Shape *iShape)
{
    iShape->changeCanvasSize(canvasSizeX, canvasSizeY);
    storage.push_back(iShape);
}

void ShapeStorage::drawAllShapes(QPainter *painter)
{
    for (Shape *shape : storage)
    {
        shape->draw(painter);
    }
}

bool ShapeStorage::selectShapeToCoord(int iX, int iY)
{
    bool result = false;
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY) && !shape->isSelect())
        {
            shape->select();
            result = true;
        }
    }
    return result;
}

bool ShapeStorage::unSelectShapeToCoord(int iX, int iY)
{
    bool result = false;
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY) && shape->isSelect())
        {
            shape->unSelect();
            result = true;
        }
    }
    return result;
}

void ShapeStorage::selectAll()
{
    for (Shape *shape : storage)
    {
        shape->select();
    }
}

void ShapeStorage::unselectAll()
{
    for (Shape *shape : storage)
    {
        shape->unSelect();
    }
}

void ShapeStorage::removeSelectedShapes()
{
    for (auto it = storage.begin(); it != storage.end();)
    {
        Shape* shape = *it;
        if (shape->isSelect())
        {
            delete shape;
            it = storage.erase(it);
        }
        else
            ++it;
    }
}

void ShapeStorage::moveSelectedShapesRelative(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isSelect())
            shape->changeRelativeCoord(iX, iY);
    }
}

bool ShapeStorage::isExistsSelectedShapes()
{
    for (Shape *shape : storage)
    {
        if (shape->isSelect())
            return true;
    }
    return false;
}

bool ShapeStorage::isExistsSelectedToCoord(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY))
            return shape->isSelect();
    }
    return false;
}

bool ShapeStorage::isExistsShapeToCoord(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY))
            return true;
    }
    return false;
}

void ShapeStorage::changeCanvasSize(int iX, int iY)
{
    canvasSizeX = iX;
    canvasSizeY = iY;
    for (Shape *shape : storage)
        shape->changeCanvasSize(iX, iY);
}

void ShapeStorage::resizeSelectedShapesRelative(int iSize)
{
    for (Shape *shape : storage)
    {
        if (shape->isSelect())
            shape->relativeResize(iSize);
    }
}

bool ShapeStorage::isResizeAreaShapeSelectedToCoord(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isSelect() && shape->isResizeArea(iX, iY))
            return true;
    }
    return false;
}

void ShapeStorage::changeColorSelectedShapes(QColor color)
{
    for (Shape *shape : storage)
    {
        if (shape->isSelect())
            shape->setColor(color);
    }
}

