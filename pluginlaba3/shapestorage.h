#ifndef SHAPESTORAGE_H
#define SHAPESTORAGE_H

#include <QDebug>
#include <vector>
#include "shape.h"
#include "groupshape.h"
#include <QFile>
#include <QRegularExpression>
#include "shapefactory.h"
#include "shapeloader.h"

enum class TypeShape {
    ALL = 0,
    SELECTED = 1,
    UNSELECTED = 2,
    RESIZE_AREA = 3,
    TO_COORDS = 4,
    TO_COORDS_UNSELECTED = 5,
    TO_COORDS_SELECTED = 6,
    RESIZE_AREA_SELECTED = 7,
    SELECTED_IS_GROUP = 8
};
struct FilterShape
{
    TypeShape type = TypeShape::ALL;
    int x = 0;
    int y = 0;

    FilterShape(TypeShape iType=TypeShape::ALL, int iX=0, int iY=0) : type(iType), x(iX), y(iY)
    {

    }
};

using namespace std;

class ShapeStorage
{
public:
    Shape* createShape(int x, int y, QColor color = Qt::green);
    vector<Shape*> get(FilterShape type);
    vector<Shape*> clone(FilterShape type);
    void add(Shape *iShape);
    void draw(FilterShape params, QPainter *painter);
    bool select(FilterShape params);
    bool unSelect(FilterShape params);
    void remove(FilterShape params);
    void remove(Shape* iShape);
    void moveRelative(FilterShape params, int x, int y);
    void moveRelative(Shape* shape, int x, int y);
    void resizeRelative(FilterShape params, int iSize);
    void resizeRelative(Shape* shape, int iSize);
    bool isExists(FilterShape params);
    void changeCanvasSize(int x, int y);
    void changeColor(FilterShape params, QColor color);
    void changeColor(Shape* shape, QColor color);
    void addGroup(FilterShape params);
    void unGroup(FilterShape params);
    int count(FilterShape params);
    void changeShapeType(Shape* shape, QString newType);

    void saveInFile(QString iFile);
    void load(QString iFile);

private:
    vector<Shape*> storage;
    vector<Shape*> createShapes(QTextStream &in);
    int canvasSizeX = 0;
    int canvasSizeY = 0;
};


#endif // SHAPESTORAGE_H
