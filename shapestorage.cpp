#include "shapestorage.h"
using namespace std;
ShapeStorage::ShapeStorage()
{

}

void ShapeStorage::add(Shape *iShape)
{
    storage.push_back(iShape);
}

void ShapeStorage::drawAllShapes(QPainter *painter)
{
    for (Shape *shape : storage)
    {
        shape->draw(painter);
    }
}

// bool ShapeStorage::selectShapeToCoord(int iX, int iY, bool unSelectOther)
// {
//     bool result = false;
//     for (Shape *shape : storage)
//     {
//         if (shape->isClicked(iX, iY))
//         {
//             if (shape->isSelect())
//                 shape->unSelect();
//             else
//                 shape->select();
//             result = true;
//         }
//         else if (!unSelectOther)
//             shape->unSelect();
//     }
//     return result;
// }

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

bool ShapeStorage::isExistsSelectedToCoors(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY))
            return shape->isSelect();
    }
    return false;
}

bool ShapeStorage::isExistsShapeToCoors(int iX, int iY)
{
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY))
            return true;
    }
    return false;
}
