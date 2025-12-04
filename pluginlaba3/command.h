#ifndef COMMAND_H
#define COMMAND_H
#include <stack>
#include "shapestorage.h"
using namespace std;
class Command
{
protected:
    ShapeStorage& storage;
    int id;

public:
    Command(ShapeStorage &iStorage);
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddShape: public Command
{
private:
    Shape* shape;
public:
    AddShape(ShapeStorage &iStorage, int x, int y, QColor color, QString type);
    void execute() override;
    void undo() override;
};

class RemoveShape: public Command
{
private:
    vector<Shape*> shapes;

public:
    RemoveShape(ShapeStorage &iStorage, FilterShape iParams);
    void execute() override;
    void undo() override;
};

class MoveShape: public Command
{
private:
    int dx, dy;
    vector<Shape*> shapes;

public:
    MoveShape(ShapeStorage &iStorage, FilterShape iParams, int idx, int idy);
    void execute() override;
    void undo() override;
};

class ResizeShape: public Command
{
private:
    int dSize;
    vector<Shape*> shapes;

public:
    ResizeShape(ShapeStorage &iStorage, FilterShape iParams, int iSize);
    void execute() override;
    void undo() override;
};

class ChangeColorShape: public Command
{
private:
    QColor beforeColor;
    QColor afterColor;
    vector<Shape*> shapes;

public:
    ChangeColorShape(ShapeStorage &iStorage, FilterShape iParams, QColor iBeforeColor, QColor iAfterColor);
    void execute() override;
    void undo() override;
};

class GroupingShape: public Command
{
private:
    vector<Shape*> shapes;
    Shape* group = ShapeFactory::create("GroupShape", 0, 0);

public:
    GroupingShape(ShapeStorage &iStorage, FilterShape iParams);
    void execute() override;
    void undo() override;
};

class UnGroupingShape: public Command
{
private:
    vector<Shape*> groups;
    vector<Shape*> sh;
public:
    UnGroupingShape(ShapeStorage &iStorage, FilterShape iParams);
    void execute() override;
    void undo() override;
};

class ChangeShapeType: public Command
{
private:
    vector<Shape*> shapes;
    QString newType;

public:
    ChangeShapeType(ShapeStorage &iStorage, FilterShape iParams, QString newTypeShape);
    void execute() override;
    void undo() override;
};

class CommandManager
{
private:
    stack<Command*> commands;
    stack<Command*> undoCommands;
    void clearStack(stack<Command*>& stack);

public:
    void add(Command* iCommand, bool isExecute = true);
    void execute();
    void undo();
    void clear();
};

#endif // COMMAND_H
