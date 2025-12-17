#include "arrowstorage.h"

ArrowStorage::ArrowStorage(ShapeStorage *iStorage) : QObject(nullptr)
{
    storage = iStorage;
    connect(storage, &ShapeStorage::shapeDeletedBefore, this, &ArrowStorage::shapeDeletedBefore);
}

ArrowStorage::~ArrowStorage()
{
    disconnect();
    for (Arrow *arrow : arrows)
        delete arrow;
}

void ArrowStorage::addArrow(Arrow *iArrow)
{
    arrows.push_back(iArrow);
}

void ArrowStorage::draw(QPainter *painter)
{
    for (Arrow *arrow : arrows)
        arrow->draw(painter);
}

void ArrowStorage::shapeDeletedBefore(Shape* shape)
{
    arrows.erase(std::remove_if(arrows.begin(), arrows.end(), [shape](Arrow* arrow)
    {
        if (arrow->shapeIs(shape))
        {
            delete arrow;
            return true;
        }
        return false;
    }), arrows.end());
}

bool ArrowStorage::isExists(Shape *iA, Shape *iB)
{
    for (Arrow *arrow : arrows)
        if (arrow->shapeIs(iA) && arrow->shapeIs(iB))
            return true;
    return false;
}
