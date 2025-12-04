#include "shapefactory.h"
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
vector<ShapeFactory::RegisterShape> ShapeFactory::registredShapes;
void ShapeFactory::registerShape(QString name, function<Shape*(int x, int y, QColor color, int size, int id)> creator, bool isCanCreate)
{
    RegisterShape shape;
    shape.name = name;
    shape.creator = creator;
    shape.isCanCreate = isCanCreate;

    registredShapes.push_back(shape);
}

Shape* ShapeFactory::create(QString name, int x, int y, QColor color, int size, int id)
{
    for (RegisterShape shapeType : registredShapes)
        if (shapeType.name == name)
            return shapeType.creator(x, y, color, size, id);
    return nullptr;
}

Shape* ShapeFactory::clone(Shape* shape)
{
    return shape->clone();
}

Shape* ShapeFactory::changeType(Shape* shape, QString &type)
{
    for (RegisterShape shapeType : registredShapes)
        if (shapeType.name == type)
        {
            if (shape->isGroup())
            {
                dynamic_cast<GroupShape*>(shape)->changeTypeTo(type);
                return shape;
            }
            else
            {
                Shape* newShape = shapeType.creator(shape->getX(), shape->getY(), shape->getColor(), shape->getSize(), shape->getID());
                delete shape;
                return newShape;

            }
        }
    return shape;
}

vector<QString> ShapeFactory::getNames()
{
    vector<QString> names;
    for (RegisterShape shape : registredShapes)
        if (shape.isCanCreate)
            names.push_back(shape.name);
    return names;
}

vector<ShapeFactory::RegisterShape> ShapeFactory::getRegistredShapes()
{
    vector<RegisterShape> shapes;
    for (RegisterShape shape : registredShapes)
        shapes.push_back(shape);
    return shapes;
}
