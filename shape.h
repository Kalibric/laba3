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
    virtual void changeRelativeCoord(int iX, int iY);
    virtual void changeCanvasSize(int iX, int iY);
    virtual void relativeResize(int iSize) {};
    virtual bool isResizeArea(int iX, int iY) {return false;};
    void select();
    void unSelect();
    bool isSelect();
protected:
    int x = 0;
    int y = 0;
    int canvasSizeX;
    int canvasSizeY;
    bool selected = false;
};

class Circle: public Shape
{
public:
    Circle();
    Circle(int iX, int iY, int iRadius = 50);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void changeRelativeCoord(int iX, int iY) override;
    void relativeResize(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord();
protected:
    int radius = 50;
};

class Square: public Shape
{
public:
    Square();
    Square(int iX, int iY, int length);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;

protected:
    int lenght = 50;
};

class ShapeTypes final
{
public:
    ShapeTypes();
    virtual void s() = 0;
    static const QString CIRCLE;
    virtual ~ShapeTypes() {};
};

#endif // SHAPE_H
