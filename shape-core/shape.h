#ifndef SHAPE_H
#define SHAPE_H
#include <QPainter>
#include <QDebug>
#include <QPolygon>
#include <vector>
#include <QRegularExpression>
#include "shape_global.h"

using namespace std;
class SHAPE_CORE_EXPORT Shape
{
public:
    Shape();
    Shape(Shape &iShape);
    Shape(int iX, int iY, QColor iColor, int _id);
    virtual bool isContaints(int iX, int iY) { return false; }
    virtual void draw(QPainter *painter) {}
    virtual void changeCanvasSize(int iX, int iY);
    virtual void resizeRelative(int iSize) {}
    virtual bool isResizeArea(int iX, int iY) { return false; }
    virtual bool validateCoord(int iX, int iY);
    virtual bool validateCoordRelative(int iX, int iY);
    virtual void correctionCoord();
    virtual void changeColor(QColor iColor);
    virtual void select();
    virtual void unSelect();
    virtual bool isSelect();
    virtual void moveRelative(int iX, int iY);
    virtual void saveInFile(QTextStream &out, int level) = 0;
    virtual void load(QTextStream &file, QString &text) = 0;
    virtual Shape* clone() = 0;
    virtual int getSize() = 0;
    virtual string type();
    int getX() { return x; }
    int getY() { return y; }
    QColor getColor() { return color; }
    int getID() { return id; }
    int getCanvasSizeX() { return canvasSizeX; }
    int getCanvasSizeY() { return canvasSizeY; }

    // Composite
    virtual bool isGroup() { return false; }
    virtual void add(Shape* child) {}
    virtual vector<Shape*> unGrouping() { return vector<Shape*>(); }


protected:
    int id;
    int x = 0;
    int y = 0;
    int canvasSizeX;
    int canvasSizeY;
    bool selected = false;
    QColor color = Qt::green;
};
#endif // SHAPE_H
