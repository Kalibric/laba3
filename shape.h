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
    virtual void select();
    virtual void unSelect();
    virtual bool isSelect() {return selected;}
    virtual void changeRelativeCoord(int iX, int iY);
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
protected:
    int radius = 50;
};

#endif // SHAPE_H
