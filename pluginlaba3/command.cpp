#include "command.h"
int idC = 0;
Command::Command(ShapeStorage *iStorage) : storage(iStorage)
{
    id = idC++;
}

// Command::Command(ArrowStorage *iArrows) : arrows(iArrows)
// {
//     id = idC++;
// }

AddShape::AddShape(ShapeStorage *iStorage, int x, int y, QColor color, QString type) : Command(iStorage)
{
    shape = ShapeFactory::create(type, x, y, color);
    id = idC++;
}

AddShape::AddShape(ShapeStorage *iStorage, Shape *iShape, bool isSaveID) : Command(iStorage)
{
    if (isSaveID)
        shape = iShape->clone();
    else if (iShape->isGroup())
    {
        vector<Shape*> shapes = iShape->clone()->unGrouping();
        shape = ShapeFactory::create("GroupShape", 0, 0);
        for (Shape *sh : shapes)
            shape->add(sh);
    }
    else
        shape = ShapeFactory::create(QString::fromStdString(shape->type()), shape->getX(), shape->getY(), shape->getColor());
}

void AddShape::execute()
{
    if (shape != nullptr)
        storage->add(shape->clone());
}

void AddShape::undo()
{
    if (shape != nullptr);
        storage->remove(shape);
}

RemoveShape::RemoveShape(ShapeStorage *iStorage, FilterShape iParams) : Command(iStorage)
{
    shapes = storage->clone(iParams);
}

void RemoveShape::execute()
{
    for (Shape* shape : shapes)
        storage->remove(shape);
}

void RemoveShape::undo()
{
    for (Shape* shape : shapes)
        storage->add(shape->clone());
}

MoveShape::MoveShape(ShapeStorage *iStorage, FilterShape iParams, int idx, int idy) : Command(iStorage), dx(idx), dy(idy)
{
    shapes = storage->clone(iParams);
}

void MoveShape::execute()
{
    for (Shape* shape : shapes)
        storage->moveRelative(shape, dx, dy);
}

void MoveShape::undo()
{
    for (Shape* shape : shapes)
        storage->moveRelative(shape, -dx, -dy);
}

ResizeShape::ResizeShape(ShapeStorage *iStorage, FilterShape iParams, int iSize) : Command(iStorage), dSize(iSize)
{
    shapes = storage->clone(iParams);
}

void ResizeShape::execute()
{
    for (Shape* shape : shapes)
        storage->resizeRelative(shape, dSize);
}

void ResizeShape::undo()
{
    for (Shape* shape : shapes)
        storage->resizeRelative(shape, -dSize);
}

ChangeColorShape::ChangeColorShape(ShapeStorage *iStorage, FilterShape iParams, QColor iBeforeColor, QColor iAfterColor) : Command(iStorage), beforeColor(iBeforeColor), afterColor(iAfterColor)
{
    shapes = storage->clone(iParams);
}

void ChangeColorShape::execute()
{
    for (Shape* shape : shapes)
        storage->changeColor(shape, afterColor);
}

void ChangeColorShape::undo()
{
    for (Shape* shape : shapes)
        storage->changeColor(shape, beforeColor);
}

GroupingShape::GroupingShape(ShapeStorage *iStorage, FilterShape iParams) : Command(iStorage)
{
    shapes = storage->clone(iParams);
    for (Shape* shape : shapes)
        group->add(shape->clone());
}

void GroupingShape::execute()
{
    storage->add(group->clone(), false);
    storage->remove(shapes);
}

void GroupingShape::undo()
{
    vector<Shape*> clone;
    storage->remove(group, false);
    for (Shape* shape : shapes)
        clone.push_back(shape->clone());

    storage->add(clone);
}

UnGroupingShape::UnGroupingShape(ShapeStorage *iStorage, FilterShape iParams) : Command(iStorage)
{
    groups = storage->clone(iParams);
    for (Shape* group : groups)
    {
        Shape* cloneGroup = group->clone();
        vector<Shape*> shapes = cloneGroup->unGrouping();
        for (Shape* shape : shapes)
            sh.push_back(shape);
    }
}

void UnGroupingShape::execute()
{
    vector<Shape*> shapes;
    for (Shape* shape : sh)
        shapes.push_back(shape->clone());
    storage->remove(groups, false);
    storage->add(shapes);
    }

void UnGroupingShape::undo()
{
    vector<Shape*> temp;
    for (Shape* group : groups)
        temp.push_back(group->clone());
    storage->add(temp, false);
    storage->remove(sh);
}

ChangeShapeType::ChangeShapeType(ShapeStorage *iStorage, FilterShape iParams, QString newTypeShape) : Command(iStorage), newType(newTypeShape)
{
    shapes = storage->clone(iParams);
}

void ChangeShapeType::execute()
{
    storage->changeShapeType(shapes, newType);
}

void ChangeShapeType::undo()
{
    vector<Shape*> temp;
    for (Shape* shape : shapes)
        temp.push_back(shape->clone());

    storage->remove(shapes, false);
    storage->add(temp);
}

// AddUniArrow::AddUniArrow(ShapeStorage *iStorage, Shape *iFirst, Shape *iSecond) : Command(iStorage)
// {
//     first = iFirst->clone();
//     second = iSecond->clone();
// }

// void AddUniArrow::execute()
// {
//     arrows->addArrow(new UniArrow(first, second));
// }

// void AddUniArrow::undo()
// {

// }

void CommandManager::clearStack(stack<Command*>& stack)
{
    while (!stack.empty())
    {
        delete stack.top();
        stack.pop();
    }
}

void CommandManager::add(Command* iCommand, bool isExecute)
{
    if (isExecute)
        iCommand->execute();
    commands.push(iCommand);
    clearStack(undoCommands);
}

void CommandManager::undo()
{
    if (!commands.empty())
    {
        Command* undoCommand = commands.top();
        undoCommand->undo();
        undoCommands.push(undoCommand);
        commands.pop();
    }
}

void CommandManager::execute()
{
    if (!undoCommands.empty())
    {
        Command* command = undoCommands.top();
        command->execute();
        commands.push(command);
        undoCommands.pop();
    }
}

void CommandManager::clear()
{
    clearStack(commands);
    clearStack(undoCommands);
}
