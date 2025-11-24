#include "command.h"

Command::Command(ShapeStorage &iStorage) : storage(iStorage)
{

}

AddShape::AddShape(ShapeStorage &iStorage, Shape* iShape) : Command(iStorage), shape(iShape)
{

}

void AddShape::execute()
{
    storage.add(shape);
}

void AddShape::undo()
{
    storage.remove(shape);
}

RemoveShape::RemoveShape(ShapeStorage &iStorage, Shape *iShape) : Command(iStorage)
{
    // shape = new
}

void RemoveShape::execute()
{

}

void RemoveShape::undo()
{

}
