#ifndef COMMAND_H
#define COMMAND_H
#include <stack>
#include "shapestorage.h"
using namespace std;
class Command
{
protected:
    ShapeStorage storage;
    virtual void execute() = 0;
    virtual void undo() = 0;

public:
    Command(ShapeStorage &iStorage);
};

class AddShape: public Command
{
private:
    Shape* shape;
public:
    AddShape(ShapeStorage &iStorage, Shape* iShape);
    void execute() override;
    void undo() override;
};

class RemoveShape: public Command
{
private:
    Shape* shape;

public:
    RemoveShape(ShapeStorage &iStorage, Shape* iShape);
    void execute() override;
    void undo() override;
};

class CommandManager
{
private:
    stack<Command*> commands;

public:
    void s();
};

#endif // COMMAND_H
