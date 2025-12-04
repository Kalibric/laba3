#include "groupshape.h"
#include "shapefactory.h"
GroupShape::GroupShape()
{
    storage.clear();
}

GroupShape::GroupShape(int iX, int iY, QColor iColor, int length, int _id)
{
    storage.clear();
}

GroupShape::GroupShape(GroupShape &iGroup)
{
    id = iGroup.id;
    for (Shape* shape : iGroup.storage)
    {
        storage.push_back(shape->clone());
    }
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

void GroupShape::resizeRelative(int iSize)
{
    for (auto shape : storage)
        shape->resizeRelative(iSize);
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
        if (!shape->validateCoord(iX, iY))
            return false;
    return true;
}

bool GroupShape::validateCoordRelative(int iX, int iY)
{
    for (Shape* shape : storage)
        if (!shape->validateCoordRelative(iX, iY))
            return false;
    return true;
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
    if (!validateCoordRelative(iX, iY))
        return;
    for (auto shape : storage)
        shape->moveRelative(iX, iY);
}

void GroupShape::saveInFile(QTextStream &out, int level)
{
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "<GroupShape>" << "\n";
    for (auto shape : storage)
        shape->saveInFile(out, level + 1);
    for (int i = 0; i < level * 2; i++)
        out << " ";
    out << "</GroupShape>" << "\n";
}

void GroupShape::add(Shape* shape)
{
    storage.push_back(shape);
}

void GroupShape::changeTypeTo(QString newType)
{
    for (size_t i = 0; i < storage.size(); ++i)
        storage[i] = ShapeFactory::changeType(storage[i], newType);
}

GroupShape* GroupShape::clone()
{
    return new GroupShape(*this);
}

vector<Shape*> GroupShape::unGrouping()
{
    vector<Shape*> result;
    for (auto shape : storage)
        result.push_back(shape);
    storage.clear();
    return result;
}

bool GroupShape::isGroup()
{
    return true;
}

void GroupShape::load(QTextStream &file, QString &line)
{
    for (Shape* shape : storage)
        delete shape;

    storage.clear();
    storage = ShapeLoader::load(file);
}
