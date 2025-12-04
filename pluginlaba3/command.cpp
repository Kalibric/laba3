#include "command.h"
int idC = 0;
Command::Command(ShapeStorage &iStorage) : storage(iStorage)
{
    id = idC++;
}

AddShape::AddShape(ShapeStorage &iStorage, int x, int y, QColor color, QString type) : Command(iStorage)
{
    shape = ShapeFactory::create(type, x, y, color);
    id = idC++;
}

void AddShape::execute()
{
    if (shape != nullptr)
        storage.add(shape->clone());
}

void AddShape::undo()
{
    if (shape != nullptr);
        storage.remove(shape);
}

RemoveShape::RemoveShape(ShapeStorage& iStorage, FilterShape iParams) : Command(iStorage)
{
    shapes = storage.clone(iParams);
}

void RemoveShape::execute()
{
    for (Shape* shape : shapes)
        storage.remove(shape);
}

void RemoveShape::undo()
{
    for (Shape* shape : shapes)
        storage.add(shape->clone());
}

MoveShape::MoveShape(ShapeStorage& iStorage, FilterShape iParams, int idx, int idy) : Command(iStorage), dx(idx), dy(idy)
{
    shapes = storage.clone(iParams);
}

void MoveShape::execute()
{
    for (Shape* shape : shapes)
        storage.moveRelative(shape, dx, dy);
}

void MoveShape::undo()
{
    for (Shape* shape : shapes)
        storage.moveRelative(shape, -dx, -dy);
}

ResizeShape::ResizeShape(ShapeStorage &iStorage, FilterShape iParams, int iSize) : Command(iStorage), dSize(iSize)
{
    shapes = storage.clone(iParams);
}

void ResizeShape::execute()
{
    for (Shape* shape : shapes)
        storage.resizeRelative(shape, dSize);
}

void ResizeShape::undo()
{
    for (Shape* shape : shapes)
        storage.resizeRelative(shape, -dSize);
}

ChangeColorShape::ChangeColorShape(ShapeStorage &iStorage, FilterShape iParams, QColor iBeforeColor, QColor iAfterColor) : Command(iStorage), beforeColor(iBeforeColor), afterColor(iAfterColor)
{
    shapes = storage.clone(iParams);
}

void ChangeColorShape::execute()
{
    for (Shape* shape : shapes)
        storage.changeColor(shape, afterColor);
}

void ChangeColorShape::undo()
{
    for (Shape* shape : shapes)
        storage.changeColor(shape, beforeColor);
}

GroupingShape::GroupingShape(ShapeStorage &iStorage, FilterShape iParams) : Command(iStorage)
{
    shapes = storage.clone(iParams);
    for (Shape* shape : shapes)
        group->add(shape->clone());
}

void GroupingShape::execute()
{
    storage.add(group->clone());
    for (Shape* shape : shapes)
        storage.remove(shape);
}

void GroupingShape::undo()
{
    storage.remove(group);
    for (Shape* shape : shapes)
        storage.add(shape->clone());
}

UnGroupingShape::UnGroupingShape(ShapeStorage &iStorage, FilterShape iParams) : Command(iStorage)
{
    groups = storage.clone(iParams);
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
    for (Shape* group : groups)
        storage.remove(group);
    for (Shape* shape : sh)
        storage.add(shape->clone());
}

void UnGroupingShape::undo()
{
    for (Shape* group : groups)
        storage.add(group->clone());
    for (Shape* shape : sh)
        storage.remove(shape);
}

ChangeShapeType::ChangeShapeType(ShapeStorage &iStorage, FilterShape iParams, QString newTypeShape) : Command(iStorage), newType(newTypeShape)
{
    shapes = storage.clone(iParams);
}

void ChangeShapeType::execute()
{
    for (Shape* shape : shapes)
        storage.changeShapeType(shape, newType);
}

void ChangeShapeType::undo()
{
    for (Shape* shape : shapes)
        storage.remove(shape);
    for (Shape* shape : shapes)
        storage.add(shape->clone());
}

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
