#include "groupshape.h"
#include "shapefactory.h"
GroupShape::GroupShape()
{
    selected = true;
    updateBounds();
}

GroupShape::GroupShape(int iX, int iY, QColor iColor, int length, int _id)
{
    storage.clear();
    selected = true;
    updateBounds();
}

GroupShape::GroupShape(GroupShape &iGroup)
{
    id = iGroup.id;
    for (Shape* shape : iGroup.storage)
    {
        storage.push_back(shape->clone());
    }
    selected = true;
    updateBounds();
}

GroupShape::~GroupShape()
{

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
    if (selected)
    {
        painter->setPen(QPen(Qt::white, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(minX, minY, maxX - minX, maxY - minY);
    }
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
    updateBounds();
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
    selected = true;
    for (auto shape : storage)
        shape->select();
}

void GroupShape::unSelect()
{
    selected = false;
    for (auto shape : storage)
        shape->unSelect();
}

bool GroupShape::isSelect()
{
    return selected;
}

void GroupShape::moveRelative(int iX, int iY)
{
    if (!validateCoordRelative(iX, iY))
        return;
    for (auto shape : storage)
        shape->moveRelative(iX, iY);
    for (callback c : onMoved)
        c.func(iX, iY);
    updateBounds();
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
    updateBounds();
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

int GroupShape::getSize()
{
    int lx = maxX - minX;
    int ly = maxY - minY;
    return lx < ly ? lx : ly;
}

void GroupShape::setSize(int size)
{
    for (Shape* shape : storage)
    {
        shape->setSize(size);
    }
}

vector<Shape*> GroupShape::unGrouping()
{
    vector<Shape*> result;
    for (auto shape : storage)
        result.push_back(shape);
    storage.clear();
    updateBounds();
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

string GroupShape::type()
{
    return "GroupShape";
}

void GroupShape::updateBounds()
{
    if (storage.size() > 0)
    {
        if (storage[0]->isGroup())
        {
            GroupShape* group = dynamic_cast<GroupShape*>(storage[0]);
            if (group == nullptr)
                return;
            minX = group->getX() - group->getSizeX() / 2;
            minY = group->getY() - group->getSizeY() / 2;
            maxX = group->getX() + group->getSizeX() / 2;
            maxY = group->getY() + group->getSizeY() / 2;
        }
        else
        {
            minX = storage[0]->getX() - storage[0]->getSize();
            minY = storage[0]->getY() - storage[0]->getSize();
            maxX = storage[0]->getX() + storage[0]->getSize();
            maxY = storage[0]->getY() + storage[0]->getSize();
        }
    }
    for (Shape *shape : storage)
    {
        if (shape->isGroup())
        {
            GroupShape* group = dynamic_cast<GroupShape*>(shape);
            if (group == nullptr)
                return;
            if (group->getX() - group->getSizeX() / 2 < minX)
                minX = group->getX() - group->getSizeX() / 2;
            if (group->getY() - group->getSizeY() / 2 < minY)
                minY = group->getY() - group->getSizeY() / 2;
            if (group->getX() + group->getSizeX() / 2 > maxX)
                maxX = group->getX() + group->getSizeX() / 2;
            if (group->getY() + group->getSizeY() / 2 > maxY)
                maxY = group->getY() + group->getSizeY() / 2;
        }
        else
        {
            if (shape->getX() - shape->getSize() < minX)
                minX = shape->getX() - shape->getSize();
            if (shape->getY() - shape->getSize() < minY)
                minY = shape->getY() - shape->getSize();
            if (shape->getX() + shape->getSize() > maxX)
                maxX = shape->getX() + shape->getSize();
            if (shape->getY() + shape->getSize() > maxY)
                maxY = shape->getY() + shape->getSize();
        }
    }
    updateCenter();
}

void GroupShape::updateCenter()
{
    x = minX + (maxX - minX) / 2;
    y = minY + (maxY - minY) / 2;
}

int GroupShape::getSizeX()
{
    return maxX - minX;
}

int GroupShape::getSizeY()
{
    return maxY - minY;
}
