#ifndef COMMAND_H
#define COMMAND_H
#include <stack>
#include "shapestorage.h"
using namespace std;
class Command
{
protected:
    ShapeStorage& storage;

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
    ShapeType::FilterParams params;

public:
    RemoveShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams);
    void execute() override;
    void undo() override;
};

class MoveShape: public Command
{
private:
    int dx, dy;
    vector<Shape*> shapes;

public:
    MoveShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams, int idx, int idy);
    void execute() override;
    void undo() override;
};

class ResizeShape: public Command
{
private:
    int dSize;
    vector<Shape*> shapes;

public:
    ResizeShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams, int iSize);
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
    ChangeColorShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams, QColor iBeforeColor, QColor iAfterColor);
    void execute() override;
    void undo() override;
};

class GroupingShape: public Command
{
private:
    vector<Shape*> shapes;
    Shape* group;

public:
    GroupingShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams);
    void execute() override;
    void undo() override;
};

class UnGroupingShape: public Command
{
private:
    vector<Shape*> groups;
    vector<Shape*> sh;
public:
    UnGroupingShape(ShapeStorage &iStorage, ShapeType::FilterParams iParams);
    void execute() override;
    void undo() override;
};

class ChangeShapeType: public Command
{
private:
    vector<Shape*> old;
    vector<Shape*> now;
    QString newType;

public:
    ChangeShapeType(ShapeStorage &iStorage, ShapeType::FilterParams iParams, QString newTypeShape);
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
