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
            if (shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                result.push_back(shape);
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                result.push_back(shape);
    }

    return result;
}

void ShapeStorage::add(Shape *iShape)
{
    iShape->changeCanvasSize(canvasSizeX, canvasSizeY);
    storage.push_back(iShape);
}

void ShapeStorage::draw(ShapeType::FilterParams type, QPainter *painter)
{
    vector<Shape*> result = ShapeStorage::get(type);
    for (Shape *shape : result)
        shape->draw(painter);
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

void ShapeStorage::remove(ShapeType::FilterParams params)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* shape : result)
    {
        delete shape;
        auto it = std::find(storage.begin(), storage.end(), shape);
        if (it != storage.end())
            storage.erase(it);
    }
}

void ShapeStorage::moveRelative(ShapeType::FilterParams params, int x, int y)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape* shape : result)
        shape->moveRelative(x, y);
}

void ShapeStorage::resizeRelative(ShapeType::FilterParams params, int iSize)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->relativeResize(iSize);
}

bool ShapeStorage::isExists(ShapeType::FilterParams params)
{
    if (params.type == ShapeType::Type::ALL)
    {
        return storage.size() > 0;
    }
    else if (params.type == ShapeType::Type::SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect())
                return true;
    }
    else if (params.type == ShapeType::Type::UNSELECTED)
    {
        for (Shape* shape : storage)
            if (!shape->isSelect())
                return true;
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA)
    {
        for (Shape* shape : storage)
            if (shape->isResizeArea(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::RESIZE_AREA_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isSelect() && shape->isResizeArea(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS_UNSELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && !(shape->isSelect()))
                return true;
    }
    else if (params.type == ShapeType::Type::TO_COORDS_SELECTED)
    {
        for (Shape* shape : storage)
            if (shape->isContaints(params.x, params.y) && shape->isSelect())
                return true;
    }

    return false;
}

void ShapeStorage::changeCanvasSize(int iX, int iY)
{
    vector<Shape*> result = ShapeStorage::get(ShapeType::FilterParams(ShapeType::Type::ALL));
    canvasSizeX = iX;
    canvasSizeY = iY;
    for (Shape *shape : result)
        shape->changeCanvasSize(iX, iY);
}

void ShapeStorage::changeColor(ShapeType::FilterParams params, QColor color)
{
    vector<Shape*> result = ShapeStorage::get(params);
    for (Shape *shape : result)
        shape->changeColor(color);
}

