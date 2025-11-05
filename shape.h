#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QDebug>
#include <QPolygon>
class Shape
{
public:
    Shape();
    virtual bool isClicked(int iX, int iY) { return false; };
    virtual void draw(QPainter *painter) {};
    virtual void changeCanvasSize(int iX, int iY);
    virtual void relativeResize(int iSize) {};
    virtual bool isResizeArea(int iX, int iY) {return false;};
    virtual bool validateCoord(int iX, int iY);
    void setColor(QColor iColor);
    void select();
    void unSelect();
    bool isSelect();
    void changeRelativeCoord(int iX, int iY);
protected:
    int x = 0;
    int y = 0;
    int canvasSizeX;
    int canvasSizeY;
    bool selected = false;
    QColor color = Qt::green;

};

class Circle: public Shape
{
public:
    Circle();
    Circle(int iX, int iY, QColor iColor, int iRadius = 50);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void relativeResize(int iSize) override;
    bool isResizeArea(int iX, int iY) override;
    bool validateCoord(int iX, int iY) override;
protected:
    int radius = 50;
};

class Square: public Shape
{
public:
    Square();
    Square(int iX, int iY, QColor iColor, int length = 50);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void relativeResize(int iSize) override;
    bool validateCoord(int iX, int iY) override;
    bool isResizeArea(int iX, int iY) override;

protected:
    int lenght = 50;
};

class Triangle: public Shape
{
public:
    // Triangle();
    Triangle(int iX, int iY, QColor iColor, int h = 50);
    bool isClicked(int iX, int iY) override;
    void draw(QPainter *painter) override;
    void relativeResize(int iSize) override;
    bool validateCoord(int iX, int iY) override;
    bool isResizeArea(int iX, int iY) override;
protected:
    int h = 50;
};

class ShapeTypes final
{
public:
    ShapeTypes();
    virtual void s() = 0;
    static const QString CIRCLE;
    static const QString SQUARE;
    static const QString TRIANGLE;
    virtual ~ShapeTypes() {};
};

#endif // SHAPE_H
