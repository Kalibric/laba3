#include "shapestorage.h"
using namespace std;
ShapeStorage::ShapeStorage()
{

}

vector<Shape*> ShapeStorage::get(ShapeType::FilterParams params)
{
    vector<Shape*> result;
    if (params.type == ShapeType::Type::ALL)
    {
        result = storage;
    }
    else if (params.type == ShapeType::Type::SELECTED)
    {
        for (Shape* shape : storage)
        {
            if (shape->isSelect())
                result.push_back(shape);
        }
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
        {
            if (shape->isResizeArea(0, 0))
                result.push_back(shape);
        }
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
        {
            if (shape->isClicked(params.x, params.y))
                result.push_back(shape);
        }
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
        {
            if (shape->isClicked(params.x, params.y) && !(shape->isSelect()))
                result.push_back(shape);
        }
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
        {
            if (shape->isClicked(param.x, params.y) && shape->isSelect())
                result.push_back(shape);
        }
    }

    return result;
}

void ShapeStorage::add(Shape *iShape)
{
    iShape->changeCanvasSize(canvasSizeX, canvasSizeY);
    storage.push_back(iShape);
}

void ShapeStorage::draw(QPainter *painter, ShapeType::FilterParams type)
{
    vector<Shape*> result = ShapeStorage::get(type);
    for (Shape *shape : result)
    {
        shape->draw(painter);
    }
}

bool ShapeStorage::select(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->select();

    return result.size() > 0;
}

bool ShapeStorage::unSelect(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->unSelect();
    return result.size() > 0;
}

void ShapeStorage::remove()
{
    // vector<Shape*> result = ShapeStorage::get(params);
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

