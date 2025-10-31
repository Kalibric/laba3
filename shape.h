#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QDebug>
class Shape
{
public:
    Shape();
    virtual bool isClicked(int iX, int iY) { return false; };
    virtual void draw(QPainter *painter) {};
    virtual void select() {};
    virtual void unSelect() {};
    bool getSelect() {return selected;}
protected:
    int x = 0;
    int y = 0;
    bool selected = false;
};

class Circle: public Shape
{
public:
    Circle();
    Circle(int iX, int iY, int iRadius = 50);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void select() override;
    void unSelect() override;
protected:
    int radius = 50;
};

#endif // SHAPE_H
