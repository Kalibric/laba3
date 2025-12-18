#include "arrowstorage.h"

ArrowStorage::ArrowStorage(ShapeStorage *iStorage) : QObject(nullptr)
{
    storage = iStorage;
    connect(storage, &ShapeStorage::shapeDeletedBefore, this, &ArrowStorage::shapeDeletedBefore);
}

ArrowStorage::~ArrowStorage()
{
    disconnect();
    for (ArrowEntry *entry : arrows)
    {
        delete entry->arrow;
        delete entry;
    }
}

int ArrowStorage::add(Arrow *iArrow)
{
    int id = arrowID++;
    arrows.push_back(new ArrowEntry{id, iArrow});
    return id;
}

void ArrowStorage::draw(QPainter *painter)
{
    for (ArrowEntry *entry : arrows)
        entry->arrow->draw(painter);
}

void ArrowStorage::shapeDeletedBefore(Shape* shape)
{
    arrows.erase(std::remove_if(arrows.begin(), arrows.end(), [shape](ArrowEntry* entry)
    {
        if (entry->arrow->shapeIs(shape))
        {
            delete entry->arrow;
            delete entry;
            return true;
        }
        return false;
    }), arrows.end());
}

bool ArrowStorage::isExists(Shape *iA, Shape *iB)
{
    for (ArrowEntry *entry : arrows)
        if (entry->arrow->shapeIs(iA) && entry->arrow->shapeIs(iB))
            return true;
    return false;
}

void ArrowStorage::remove(int id)
{
    arrows.erase(std::remove_if(arrows.begin(), arrows.end(),
        [id](ArrowEntry* entry)
        {
            if (entry->id == id)
            {
                delete entry->arrow;
                delete entry;
                return true;
            }
            return false;
        }), arrows.end());
}
