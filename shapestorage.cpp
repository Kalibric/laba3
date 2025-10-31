#include "shapestorage.h"
using namespace std;
ShapeStorage::ShapeStorage()
{

}

void ShapeStorage::add(Shape *iShape)
{
    storage.push_back(iShape);
}

void ShapeStorage::drawAll(QPainter *painter)
{
    for (Shape *shape : storage)
    {
        shape->draw(painter);
    }
}

bool ShapeStorage::selectShape(int iX, int iY, bool unSelectOther)
{
    bool result = false;
    for (Shape *shape : storage)
    {
        if (shape->isClicked(iX, iY))
        {
            if (shape->getSelect())
                shape->unSelect();
            else
                shape->select();
            result = true;
        }
        else if (!unSelectOther)
            shape->unSelect();
    }
    return result;
}

void ShapeStorage::removeSelectedShapes()
{
    for (auto it = storage.begin(); it != storage.end();)
    {
        Shape* shape = *it;
        if (shape->getSelect())
        {
            delete shape;
            it = storage.erase(it);
        }
        else
            ++it;
    }
}

void removeShape(Shape *iShape)
{

}
