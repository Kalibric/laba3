#include "command.h"

Command::Command(ShapeStorage &iStorage) : storage(iStorage)
{

}

AddShape::AddShape(ShapeStorage &iStorage, int x, int y, QColor color, QString type) : Command(iStorage)
{
    shape = ShapeFactory::create(type, x, y, color);
}

void AddShape::execute()
{
    storage.add(shape);
}

void AddShape::undo()
{
    storage.remove(shape);
}

RemoveShape::RemoveShape(ShapeStorage& iStorage, ShapeType::FilterParams iParams) : Command(iStorage), params(iParams)
{
    vector<Shape*> iShapes = storage.clone(params);
    for (Shape* shape : iShapes)
        shapes.push_back(shape);
}

void RemoveShape::execute()
{
    storage.remove(params);
}

void RemoveShape::undo()
{
    for (Shape* shape : shapes)
        storage.add(shape);
}

MoveShape::MoveShape(ShapeStorage& iStorage, ShapeType::FilterParams iParams, int idx, int idy) : Command(iStorage), dx(idx), dy(idy)
{
    shapes = storage.get(iParams);
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

ResizeShape::ResizeShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams, int iSize) : Command(iStorage), dSize(iSize)
{
    shapes = storage.get(iParams);
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

ChangeColorShape::ChangeColorShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams, QColor iBeforeColor, QColor iAfterColor) : Command(iStorage), beforeColor(iBeforeColor), afterColor(iAfterColor)
{
    shapes = storage.get(iParams);
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

GroupingShape::GroupingShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams) : Command(iStorage)
{
    shapes = storage.get(iParams);
    group = new GroupShape();
    for (Shape* shape : shapes)
        group->add(shape);
}

void GroupingShape::execute()
{
    for (Shape* shape : shapes)
        storage.remove(shape);
    storage.add(group);
}

void GroupingShape::undo()
{
    storage.remove(group);
    for (Shape* shape : shapes)
        storage.add(shape);
}

UnGroupingShape::UnGroupingShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams) : Command(iStorage)
{
    groups = storage.get(iParams);
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
        storage.add(shape);
}

void UnGroupingShape::undo()
{
    for (Shape* group : groups)
        storage.add(group);
    for (Shape* shape : sh)
        storage.remove(shape);
}

ChangeShapeType::ChangeShapeType(ShapeStorage &iStorage, ShapeType::FilterParams iParams, QString newTypeShape) : Command(iStorage), newType(newTypeShape)
{
    old = storage.clone(iParams);
    now = storage.get(iParams);
}

void ChangeShapeType::execute()
{
    for (Shape* shape : now)
    {
        storage.changeShapeType(shape, newType);
    }
}

void ChangeShapeType::undo()
{
    for (Shape* shape : old)
    {
        storage.add(shape);
    }
    for (Shape* shape : now)
    {
        storage.remove(shape);
    }
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
